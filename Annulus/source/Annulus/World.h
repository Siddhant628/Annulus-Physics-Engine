#pragma once
#include <vector>

//#define GLM_FORCE_CXX98
//#include "glm/glm.hpp"

namespace Annulus
{
	class Settings;
	class RigidBody;

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
		* A vector of pointers to all the rigid bodies which are to be removed from this simulation.
		*/
		std::vector<RigidBody*> mBodiesDelete;
	};
}