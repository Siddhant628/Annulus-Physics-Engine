#pragma once
#include "GameClock.h"
#include "GameTime.h"

#include <chrono>
#include <vector>
#include "ParticleContactResolver.h"
#include "ParticleContactGenerator.h"

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
		/**
		* Create a particle.
		* @return A pointer to the created particle.
		*/
		Particle* CreateParticle();
		/**
		* Get a reference to the settings associated with this world.
		*/
		const Settings& GetSettings() const;
		/**
		* Get the vector of particles that are present in the world.
		*/
		const std::vector<Particle*>& GetParticles() const;
		/**
		* Register the particle contact generator from the world.
		* @param particleContactGenerator The particle that needs to be registered.
		*/
		void RegisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator);
		/**
		* Unregister the particle contact generator from the world.
		* @param particleContactGenerator The particle that needs to be unregistered.
		*/
		void UnregisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator);
	private:
		/**
		* Clears the memory taken by various objects queued for deletion.
		*/
		void ClearDeleteQueues();

		std::uint32_t GenerateContacts();
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
		/**
		* The vecotr of particle contact generators registered to the world.
		*/
		std::vector<ParticleContactGenerator*> mParticleContactGenerators;
		/**
		* A vecotr of particle contact generators that needs to be cleared.
		*/
		std::vector<ParticleContactGenerator*> mParticleContactGeneratorsDelete;
		/**
		* The list of particle contacts which are assembled in each update.
		*/
		ParticleContact* mContacts;
	};
}