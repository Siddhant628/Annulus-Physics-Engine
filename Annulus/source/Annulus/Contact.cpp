#include "pch.h"
#include "Contact.h"

#include "Collider.h"

namespace Annulus
{
	Contact::Contact(Collider& collider1, Collider& collider2) : 
		mColliders{&collider1, &collider2},
		mRestitution(1.0f)
	{

	}

	void Contact::Initialize(const glm::vec2& normal, const glm::vec2& contact, std::float_t penetration)
	{
		mContactNormal = normal;
		mContactPoint = contact;
		mPenetration = penetration;
	}

	void Contact::SetRestitution(std::float_t restitution)
	{
		assert(restitution >= 0.0f && restitution <= 1.0f);
		mRestitution = restitution;
	}
}
