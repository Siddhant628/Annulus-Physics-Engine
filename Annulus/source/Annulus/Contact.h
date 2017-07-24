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
		friend class ContactResolver;
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
		* Get the position of contact.
		*/
		const glm::vec2& GetPosition() const;
		/**
		* Get the normal direction involed in contact.
		*/
		const glm::vec2& GetNormal() const;
		/**
		* Calculate the data for this contact which will be required to resolve this contact.
		* @param seconds The amount of time taken in the previous update call.
		*/
		void CalculateInternals(std::float_t seconds);
		/**
		* Resolve the interpenetration for this contact.
		*/
		void ResolveInterpenetration();

		/**
		* Delete copy and move operations.
		*/
		Contact(const Contact&) = delete;
		Contact& operator=(const Contact& rhs) = delete;
		Contact(Contact&& rhs) = delete;
		Contact& operator=(Contact&& rhs) = delete;
	private:
		/**
		* Calculates and returns the velocity of the point of contact relative w.r.t to the rigid body associated to the collider.
		* @param index The index of the collider for which the associated rigid body's velocity needs to be caluculated.
		*/
		glm::vec2 CalculateLocalVelocity(std::uint32_t index);
		/**
		* Calculate the desired change in velocity in order to resolve this contact.
		* @param seconds The amount of time taken in the previous update call.
		* @return The desired change in velocity.
		*/
		std::float_t CalculateDesiredVelocityChange(std::float_t seconds);

		/* The data associated with the contact object. */
		/**
		* The colliders which are involved in the collision.
		*/
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

		/* The derived data used to resolve contacts. Calculated by the collision resolver for each contact which would be resolved. */
		/**
		* The closing velocity at the point of contact.
		*/
		glm::vec2 mContactVelocity;
		/**
		* The required change in velocity for this contact to be resolved.
		*/
		std::float_t mDesiredDeltaVelocity;
		/**
		* The positions of the contact point relative to the origin (center of mass) of each body.
		*/
		glm::vec2 mRelativeContactPosition[2];
		/**
		* The linear change in position when the collision is resolved.
		*/
		glm::vec2 mLinearPositionChange[2];

		/**
		* The closing velocity below which resitution is limited in order to produce good collisions.
		*/
		static const std::float_t sResitutionLimitingVelocity;
	};
}