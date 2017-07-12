#include "pch.h"
#include "AnchoredSpring.h"

#include "RigidBody.h"

namespace Annulus
{
	AnchoredSpring::AnchoredSpring(RigidBody& body, const glm::vec2& localConnection) :
		mBody(&body),
		mLocalConnectionPoint(localConnection),
		mRestLength(10),
		mSpringConstant(1),
		mAnchorPosition(glm::vec2(0, 0))
	{

	}

	void AnchoredSpring::SetRestLength(std::float_t length)
	{
		assert(length >= 0);
		mRestLength = length;
	}

	void AnchoredSpring::SetSpringConstant(std::float_t constant)
	{
		assert(constant >= 0);
		mSpringConstant = constant;
	}

	void AnchoredSpring::SetAnchor(const glm::vec2& anchor)
	{
		mAnchorPosition = anchor;
	}

	void AnchoredSpring::UpdateForce(std::float_t seconds)
	{
		seconds;
		// Get the position of connection in world coordinates.
		glm::vec2 connectionPosition;
		mBody->GetPointInWorldSpace(mLocalConnectionPoint, connectionPosition);

		// Calculate the force's direction and magnitude.
		glm::vec2 force = connectionPosition - mAnchorPosition;
		std::float_t magnitude = glm::length(force) - mRestLength;
		magnitude *= mSpringConstant;

		// Calcuate the force and apply to the body.
		force = glm::normalize(force);
		force *= -magnitude;

		mBody->AddForce(force, connectionPosition);
	}
}
