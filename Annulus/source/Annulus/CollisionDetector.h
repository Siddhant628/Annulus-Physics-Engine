#pragma once
#include <vector>

namespace Annulus
{
	class World;
	class Collider;
	class Contact;
	class Circle;


	class CollisionDetector
	{
		friend class World;
	public:
		/**
		* Free the memory allocated for contacts which are generated.
		*/
		~CollisionDetector();
	private:
		CollisionDetector();
		/**
		* Detect collision between two different colliders. It runs the right method for testing for collision based on the types of colliders.
		* @param collider1 A reference to the first collider to test for.
		* @param collider2 A reference to the second collider to test for.
		* @param contacts A reference to the vector of contacts to which the newly created contacts should be added.
		*/
		std::uint32_t DetectCollision(const Collider& collider1, const Collider& collider2, std::vector<const Contact*>& contacts);
		/**
		* Detect collision between two circles. Generates a single contact in case two circles are colliding.
		* @param collider1 A reference to the first collider to test for.
		* @param collider2 A reference to the second collider to test for.
		* @param contacts A reference to the vector of contacts to which the newly created contact should be added.
		*/
		std::uint32_t CircleAndCircle(const Circle& collider1, const Circle& collider2, std::vector<const Contact*>& contacts);
		/**
		* Generate the contacts for the given colliders.
		*/
		void GenerateContacts(const std::vector<const Collider*> colliders);
		/**
		* Call the destructors on all the contacts in the allocated memory.
		*/
		void DestroyContacts();
		/**
		* The number of contacts which are already in use.
		*/
		std::uint32_t mUsedContacts;
		/**
		* The maximum number of contacts which are allowed in the simulation.
		*/
		std::uint32_t mContactsCount;
		
		/* Related to initialization.*/
		/**
		* Initialize the collision detection system with the world.
		* @param world The world with which this collision detector is associated.
		*/
		void Initialize(const World& world);
		/**
		* A pointer to the world with which the collision detection system is associated.
		*/
		const World* mOwnerWorld;
		/**
		* The array of contacts used by the collision detector to manage contacts. New contacts are added to this array using placement new.
		*/
		Contact* mContacts;
	};
}
