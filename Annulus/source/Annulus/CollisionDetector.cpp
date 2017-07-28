#include "pch.h"
#include "CollisionDetector.h"

#include "Collider.h"
#include "Circle.h"

#include "Contact.h"
#include "World.h"
#include "Settings.h"

namespace Annulus
{
	CollisionDetector::~CollisionDetector()
	{
		DestroyContacts();
		free(mContacts);
	}

	CollisionDetector::CollisionDetector() :
		mUsedContacts(0),
		mContactsCount(0),
		mOwnerWorld(nullptr)
	{

	}

	std::uint32_t CollisionDetector::DetectCollision(const Collider& collider1, const Collider& collider2, std::vector<const Contact*>& contacts)
	{
		assert(mContactsCount != 0);
		if(collider1.GetColliderType() == ColliderType::Circle && collider2.GetColliderType() == ColliderType::Circle)
		{
			return CircleAndCircle(static_cast<const Circle&>(collider1), static_cast<const Circle&>(collider2), contacts);
		}
		return 0;
	}

	std::uint32_t CollisionDetector::CircleAndCircle(const Circle& collider1, const Circle& collider2, std::vector<const Contact*>& contacts)
	{
		// Return if not allowed to generate any contacts.
		if((mContactsCount - mUsedContacts) < 1)
		{
			return 0;
		}
		// Return if there is no contact between the circles.
		glm::vec2 normal = (collider1.GetPosition() - collider2.GetPosition());
		std::float_t distance = glm::length(normal);

		if(distance > (collider1.GetRadius() + collider2.GetRadius()))
		{
			return 0;
		}
		// Create the contact with its data.
		Contact* contact = new (mContacts + mUsedContacts)Contact(collider1, collider2);
		contact->mContactNormal = normal / distance;
		//std::cout << "Contact Normal: X= " << contact->mContactNormal.x << "  Y= " << contact->mContactNormal.y << std::endl;
		std::float_t radius1 = collider1.GetRadius();
		std::float_t radius2 = collider2.GetRadius();
		contact->mPenetration = (radius1 + radius2 - distance);
		//std::cout << "Contact Penetration: " << contact->mPenetration << std::endl;
		contact->mContactPoint = (collider1.GetPosition() * radius2 + collider2.GetPosition() * radius1) / (radius1 + radius2);
		// Add the contact to the world.
		contacts.push_back(contact);
		return 1;
	}

	void CollisionDetector::Initialize(const World& world)
	{
		mOwnerWorld = &world;
		mContactsCount = world.GetSettings().GetMaxContacts();
		mContacts = static_cast<Contact*>(malloc(sizeof(Contact)*mContactsCount));
	}

	void CollisionDetector::GenerateContacts(const std::vector<const Collider*> colliders)
	{
		for (auto it = colliders.cbegin(); it != colliders.cend(); ++it)
		{
			for (auto itOther = it; itOther != colliders.cend(); ++itOther)
			{
				// Check for contact between different colliders within same collision layer.
				if (*it != *itOther && (*it)->GetCollisionLayer() == (*itOther)->GetCollisionLayer())
				{
					mUsedContacts += DetectCollision(**it, **itOther, const_cast<World*>(mOwnerWorld)->GetContacts());
				}
			}
			if (mUsedContacts == mContactsCount)
			{
				break;
			}
		}
	}

	void CollisionDetector::DestroyContacts()
	{
		for(std::uint32_t i = 0; i < mUsedContacts; ++i)
		{
			(mContacts + i)->~Contact();
		}
		mUsedContacts = 0;
	}
}