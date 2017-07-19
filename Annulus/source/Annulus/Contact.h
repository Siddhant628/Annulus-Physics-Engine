#pragma once

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class Collider;
	/**
	* Represents the contact between two bodies. This contact is queued to the world and it is resolved for if the world can still handle more contacts.
	*/
	class Contact final
	{
		friend class CollisionDetector;
	public:
		/**
		* Constructor.
		* @param collider1 The first of the two colliders involed in the contact.
		* @param collider2 The second of the two colliders involed in the contact.
		*/
		Contact(const Collider& collider1, const Collider& collider2);
		/**
		* Destructor.
		*/
		~Contact() = default;
		/**
		* Set the restitution of this contact prior to its resolution, once it is created. Defaults to 1 (elastic collision).
		* @param restitution The magnitude of restitution to set in [0,1].
		*/
		void SetRestitution(std::float_t restitution);
		/**
		* Delete copy and move operations.
		*/
		Contact(const Contact&) = delete;
		Contact& operator=(const Contact& rhs) = delete;
		Contact(Contact&& rhs) = delete;
		Contact& operator=(Contact&& rhs) = delete;
	private:
		const Collider* mColliders[2];
		/**
		* The coefficient of restitution for this specific collision.
		*/
		std::float_t mRestitution;
		/**
		* The direction of contact between two colliders. This is a vector for collider 1 relative to collider 2.
		*/
		glm::vec2 mContactNormal;
		/**
		* The position of the contact in world coordinates.
		*/
		glm::vec2 mContactPoint;
		/**
		* The depth of penetration at the contact.
		*/
		std::float_t mPenetration;
	};
}