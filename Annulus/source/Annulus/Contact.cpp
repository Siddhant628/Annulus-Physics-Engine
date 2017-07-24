#include "pch.h"
#include "Contact.h"

#include "Collider.h"
#include "RigidBody.h"

namespace Annulus
{
	const std::float_t Contact::sResitutionLimitingVelocity = 0.25f;

	Contact::Contact(const Collider& collider1, const Collider& collider2) :
		mRestitution(1.0f),
		mColliders{ &collider1, &collider2 }
	{

	}

	void Contact::SetRestitution(std::float_t restitution)
	{
		assert(restitution >= 0.0f && restitution <= 1.0f);
		mRestitution = restitution;
	}

	const glm::vec2& Contact::GetPosition() const
	{
		return mContactPoint;
	}

	const glm::vec2& Contact::GetNormal() const
	{
		return mContactNormal;
	}

	void Contact::CalculateInternals(std::float_t seconds)
	{
		// Calculate the relative position of the contact with respect to each body.
		mRelativeContactPosition[0] = mContactPoint - mColliders[0]->GetPosition();
		mRelativeContactPosition[1] = mContactPoint - mColliders[1]->GetPosition();

		// Find the relative velocity of the bodies at the point of contact.
		mContactVelocity = CalculateLocalVelocity(0);
		mContactVelocity += CalculateLocalVelocity(1);

		// Calculate the desired change in velocity for resolution.
		  CalculateDesiredVelocityChange(seconds);
	}

	void Contact::ResolveInterpenetration()
	{
		if (mPenetration > 0)
		{
			auto& body1 = const_cast<RigidBody&>(mColliders[0]->GetBody());
			auto& body2 = const_cast<RigidBody&>(mColliders[1]->GetBody());

			std::float_t totalInverseMass = body1.GetMassInverse();
			totalInverseMass += body2.GetMassInverse();

			if (totalInverseMass > 0)
			{
				glm::vec2 movementPerIMass = mContactNormal * (mPenetration / totalInverseMass);
				// Update the positions in order to resolve interpenetrations. (Resolution)
				mLinearPositionChange[0] = (movementPerIMass * body1.GetMassInverse());
				mLinearPositionChange[1] = -(movementPerIMass * body2.GetMassInverse());
				body1.SetPosition(body1.GetPosition() + mLinearPositionChange[0]);
				body2.SetPosition(body2.GetPosition() + mLinearPositionChange[1]);
			}
		}
	}

	void Contact::ResolveVelocity()
	{
		std::float_t sign = -1;
		const RigidBody* bodies[2] = { nullptr, nullptr };
		bodies[0] = &mColliders[0]->GetBody();
		bodies[1] = &mColliders[1]->GetBody();
		// Get the impulse to apply for desired velocity in contact-coordinates.
		glm::vec2 impulse;
		CalculateFrictionlessImpulse(impulse);

		// Convert the impulse to world-coordinates.
		glm::vec2 temp = impulse;
		
		std::float_t cosine = glm::dot(-mContactNormal, glm::vec2(1, 0));
		std::float_t sine = sqrt(1 - cosine * cosine);
		impulse.x = temp.x * cosine - temp.y * sine;
		impulse.y = temp.x * sine + temp.y * cosine;

		// Split the impulse and apply to the bodies.
		for(std::uint32_t index = 0; index < 2; ++index)
		{
			if(index == 1)
			{
				sign = 1;
			}
			// Splitting.
			std::float_t impulsiveTorque = mRelativeContactPosition[index].x * impulse.y - mRelativeContactPosition[index].y * impulse.x;
			mRotationChange[index] = sign * bodies[index]->GetInertiaInverse() * impulsiveTorque;
			mVelocityChange[index] = sign * impulse * bodies[index]->GetMassInverse();

			// Applying.
			const_cast<RigidBody*>(bodies[index])->AddVelocity(mVelocityChange[index]);
			const_cast<RigidBody*>(bodies[index])->AddRotation(mRotationChange[index]);
		}
	}

	void Contact::CalculateFrictionlessImpulse(glm::vec2& impulse)
	{
		const RigidBody* bodies[2];
		bodies[0] = &mColliders[0]->GetBody();
		bodies[1] = &mColliders[0]->GetBody();

		// Delta velocity is the change in velocity at the point of contact per unit impulse.
		std::float_t deltaVelocity = 0.0f;
		
		// Add the change in velocity per unit impulse for linear component of velocity change.
		deltaVelocity += bodies[0]->GetMassInverse();
		deltaVelocity += bodies[1]->GetMassInverse();

		// Add the change in velocity per unit impulse due to angular component of velocity change.
		for (std::uint32_t index = 0; index < 2; ++index)
		{
			std::float_t deltaVelocityWorld = mRelativeContactPosition[index].x * mContactNormal.y - mRelativeContactPosition[index].y * mContactNormal.x;
			deltaVelocityWorld *= bodies[index]->GetInertiaInverse();
			glm::vec2 deltaVelocityOfPoint = glm::vec2(- deltaVelocityWorld * mRelativeContactPosition[index].y , deltaVelocityWorld * mRelativeContactPosition[index].x);
			deltaVelocity += glm::dot(deltaVelocityOfPoint, mContactNormal);
		}

		impulse.x = mDesiredDeltaVelocity / deltaVelocity;
		impulse.y = 0.0f;
	}

	glm::vec2 Contact::CalculateLocalVelocity(std::uint32_t index)
	{
		assert(index == 0 || index == 1);
		glm::vec2 calculatedVelocity, temp;
		const RigidBody& body = mColliders[index]->GetBody();

		// Calculate the velocity in world coordinates.
		glm::vec3 velocity = glm::cross(glm::vec3(mRelativeContactPosition[index].x, mRelativeContactPosition[index].y, 0), glm::vec3(0, 0, body.GetRotation()));
		calculatedVelocity.x = velocity.x;
		calculatedVelocity.y = velocity.y;
		calculatedVelocity += body.GetVelocity();

		// Convert the velocity into contact coordinates.
		temp = calculatedVelocity;
		if (index == 0)
		{
			calculatedVelocity.x = glm::dot(temp, mContactNormal);
			calculatedVelocity.y = glm::dot(temp, glm::vec2(-mContactNormal.y, mContactNormal.x));
		}
		else
		{
			calculatedVelocity.x = glm::dot(temp, -1.0f * mContactNormal);
			calculatedVelocity.y = glm::dot(temp, -1.0f * glm::vec2(-mContactNormal.y, mContactNormal.x));
		}

		return calculatedVelocity;
	}

	void Contact::CalculateDesiredVelocityChange(std::float_t seconds)
	{
		const RigidBody& body1 = mColliders[0]->GetBody();
		const RigidBody& body2 = mColliders[1]->GetBody();

		// Calculate the acceleration induced velocity this frame.
		std::float_t velocityDueToAcceleration = 0;
		velocityDueToAcceleration += glm::dot(body1.GetLastFrameAccelerationLinear() * seconds, mContactNormal);
		velocityDueToAcceleration += glm::dot(body2.GetLastFrameAccelerationLinear() * seconds, -mContactNormal);

		// Limit the resitution if the velocity is very low.
		if (std::abs(mContactVelocity.x) < sResitutionLimitingVelocity)
		{
			mRestitution = 0.0f;
		}

		// Calculate the desired delta velocity.
		mDesiredDeltaVelocity = -mContactVelocity.x - (mContactVelocity.x - velocityDueToAcceleration) * mRestitution;
	}
}
