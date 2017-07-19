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
	private:
		CollisionDetector();

		std::uint32_t DetectCollision(const Collider& collider1, const Collider& collider2, std::vector<const Contact*>& contacts);
	
		std::uint32_t CircleAndCircle(const Circle& collider1, const Circle& collider2, std::vector<const Contact*>& contacts);
		/**
		* Generate the contacts for the given colliders.
		*/
		void GenerateContacts(const std::vector<const Collider*> colliders);
		
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
	};
}
