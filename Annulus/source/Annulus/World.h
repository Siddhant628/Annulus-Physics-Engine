#pragma once

#include <chrono>

#include "GameClock.h"
#include "GameTime.h"

namespace Annulus
{
	class Settings;	

	/**
	* A class which manages all physics entities.
	*/
	class World
	{
	public:
		/**
		* Constructor.
		* @param settings The settings for the world which are used to be used by it to perform update of all of its contained bodies.
		*/
		World(Settings& settings);
		/**
		* Destructor.
		*/
		~World() = default;
		/**
		* The actual physics update method which performs an update on all the bodies present in this world.
		* @param The amount of time that has passed since last update of the game loop.
		*/
		void Update(std::chrono::nanoseconds nanoseconds);
	private:
		/**
		* The settings with which this world was initialized.
		*/
		Settings* mSettings;
		/**
		* The amount of time that has passed since the last physics update call was made.
		*/
		std::chrono::nanoseconds mTimeSinceLastUpdate;
	};
}