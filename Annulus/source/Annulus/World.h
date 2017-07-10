#pragma once

//#define GLM_FORCE_CXX98
//#include "glm/glm.hpp"

namespace Annulus
{
	class Settings;
	/**
	* A class which manages all physics entities for the 2D rigid body physics engine.
	*/
	class World
	{
	public:
		/**
		* Constructor.
		* @param settings The settings for the world which are used to be used by it to perform update of all of its contained bodies.
		*/
		World(const Settings& settings);
		/**
		* Destructor.
		* Destroys and frees the memory allocated to any physics simulation objects in the world.
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
	private:
		/**
		* The settings with which this world was initialized.
		*/
		const Settings* mSettings;
		/**
		* The amount of time that has passed since the last physics update call was made.
		*/
		std::chrono::nanoseconds mTimeSinceLastUpdate;
	};
}