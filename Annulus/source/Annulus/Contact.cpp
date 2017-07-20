#include "pch.h"
#include "Contact.h"

#include "Collider.h"

namespace Annulus
{
	Contact::Contact(const Collider& collider1, const Collider& collider2) : 
		mColliders{&collider1, &collider2},
		mRestitution(1.0f)
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
}
