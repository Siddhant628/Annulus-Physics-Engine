#pragma once
#include <vector>
#include "Contact.h"

//#define GLM_FORCE_CXX98
//#include "glm/glm.hpp"

namespace Annulus
{
	class Settings;
	class RigidBody;
	class ForceGenerator;
	class Collider;
	class CollisionDetector;
	class ContactResolver;

	/**
	* A class which manages all physics entities for the 2D rigid body physics engine.
	*/
	class World final
	{
	public:
		/**
		* Constructor.
		* Initializes various associated classes.
		* @param settings The settings for the world which are used to be used by it to perform update of all of its contained bodies.
		*/
		World(const Settings& settings);
		/**
		* Destructor.
		* Destroys and frees the memory allocated to any physics simulation objects in the world which are still in scope.
		*/
		~World();
		/**
		* The actual physics update method which performs an update on all the bodies present in this world.
		* @param The amount of time that has passed since last update of the game loop.
		*/
		void Update(std::chrono::nanoseconds nanoseconds);
		/**
		* Get a the settings associated with this world.
		* @return A reference to the settings associated with this world.
		*/
		const Settings& GetSettings() const;
		/**
		* Register a rigid body to this world.
		* @param body The rigid body which has to be registered to this world.
		*/
		void RegisterBody(RigidBody& body);
		/**
		* Unregister a rigid body from this world.
		* @param body The rigid body which has to be unregistered from this world.
		*/
		void UnregisterBody(RigidBody& body);
		/**
		* Register a force generator to this world.
		* @param generator The force generator which has to be registered to this world.
		*/
		void RegisterForceGenerator(ForceGenerator& generator);
		/**
		* Unregister a force generator from this world.
		* @param generator The force generator which has to be unregistered from this world.
		*/
		void UnregisterForceGenerator(ForceGenerator& generator);
		/**
		* Register a collider to this world.
		* @param collider The collider which has to be registered to this world.
		*/
		void RegisterCollider(const Collider& collider);
		/**
		* Unregister a colliderr from this world.
		* @param collider The force generator which has to be unregistered from this world.
		*/
		void UnregisterCollider(const Collider& collider);

		/**
		* Get the vector of contacts which will be handled by the contact resolver.
		*/
		std::vector<const Contact*>& GetContacts();
	private:
		/**
		* Clears the pointers to instances of classes which are out of scope.
		* Deletes the pointers to rigid bodies from this world for each rigid body which is out of scope.
		*/
		void ClearDeleteQueues();

		/**
		* The settings with which this world was initialized.
		*/
		const Settings* mSettings;
		/**
		* The amount of time that has passed since the last physics update call was made.
		*/
		std::chrono::nanoseconds mTimeSinceLastUpdate;
		/**
		* A vector of pointers to all the rigid bodies contained in this simulation.
		*/
		std::vector<RigidBody*> mBodies;
		/**
		* A vector of pointers to all the rigid bodies which are to be removed from this simulation since out of scope.
		*/
		std::vector<RigidBody*> mBodiesDelete;
		/**
		* A vector of pointers to all the force generators contained in this simulation.
		*/
		std::vector<ForceGenerator*> mForceGenerators;
		/**
		* A vector of pointers to all the force generators which are to be removed from this simulation since out of scope.
		*/
		std::vector<ForceGenerator*> mForceGeneratorsDelete;
		/**
		* A vector of pointers to all the colliders contained in this simulation.
		*/
		std::vector<const Collider*> mColliders;
		/**
		* A vector of pointers to all the colliders which are to be removed from this simulation since out of scope.
		*/
		std::vector<const Collider*> mCollidersDelete;

		/**
		* The contacts which were generated this update and need to be handled.
		*/
		std::vector<const Contact*> mContacts;
		/**
		* The collision detector associated with this world. Created and destroyed by the world implicity.
		*/
		CollisionDetector* mCollisionDetector;
		/**
		* The contact resolver associated with this world. Created and destroyed by the world implicitly.
		*/
		ContactResolver* mContactResolver;
	};
}