#pragma once
#include "GameClock.h"
#include "GameTime.h"

#include <chrono>
#include <vector>
#include "ParticleContactResolver.h"

namespace Annulus
{
	class Settings;
	class Particle;

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
		* Destroys and frees the memory allocated to any physics simulation objects in the world.s
		*/
		~World();
		// TODO Discuss fixed time stepping with Paul.
		/**
		* The actual physics update method which performs an update on all the bodies present in this world.
		* @param The amount of time that has passed since last update of the game loop.
		*/
		void Update(std::chrono::nanoseconds nanoseconds);

		Particle* CreateParticle();

		const Settings& GetSettings() const;

		const std::vector<Particle*>& GetParticles() const;
	private:
		/**
		* The settings with which this world was initialized.
		*/
		Settings* mSettings;
		/**
		* The amount of time that has passed since the last physics update call was made.
		*/
		std::chrono::nanoseconds mTimeSinceLastUpdate;
		/**
		* A vector of particles present in this world.
		*/
		std::vector<Particle*> mParticles;
		/**
		* The particle contact resolver associated with this world. Created on contruction of the world.
		*/
		ParticleContactResolver* mParticleContactResolver;
	};
}
