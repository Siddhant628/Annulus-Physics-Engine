#include "pch.h"
#include "Gravity.h"

#include "World.h"
#include "RigidBody.h"
#include "Settings.h"

namespace Annulus
{
	Gravity::Gravity(RigidBody& body) :
		mBody(&body)
	{

	}

	void Gravity::UpdateForce(std::float_t seconds)
	{
		seconds;
		// A body with finite mass can only be affected.
		if(mBody->GetMassInverse() > 0)
		{
			glm::vec2 gravity = sOwnerWorld->GetSettings().GetGravity();
			mBody->AddForce(gravity / mBody->GetMassInverse());
		}
	}
}
