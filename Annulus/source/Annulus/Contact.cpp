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
			calculatedVelocity.x = glm::dot(temp, -1.0f * mContactNormal);
			calculatedVelocity.y = glm::dot(temp, -1.0f * glm::vec2(-mContactNormal.y, mContactNormal.x));
		}
		else
		{
			calculatedVelocity.x = glm::dot(temp, mContactNormal);
			calculatedVelocity.y = glm::dot(temp, glm::vec2(-mContactNormal.y, mContactNormal.x));
		}

		return calculatedVelocity;
	}

	std::float_t Contact::CalculateDesiredVelocityChange(std::float_t seconds)
	{
		const RigidBody& body1 = mColliders[0]->GetBody();
		const RigidBody& body2 = mColliders[1]->GetBody();

		// Calculate the acceleration induced velocity this frame.
		std::float_t velocityDueToAcceleration = 0;
		velocityDueToAcceleration += glm::dot(body1.GetLastFrameAccelerationLinear() * seconds, mContactNormal);
		velocityDueToAcceleration += glm::dot(body2.GetLastFrameAccelerationLinear() * seconds, -mContactNormal);

		// Limit the resitution if the velocity is very low.
		if (mContactVelocity.x < sResitutionLimitingVelocity)
		{
			mRestitution = 0.0f;
		}

		// Calculate the desired delta velocity.
		return -mContactVelocity.x - (mContactVelocity.x - velocityDueToAcceleration) * mRestitution;
	}
}
