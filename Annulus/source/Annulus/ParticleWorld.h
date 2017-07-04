#pragma once
#include "GameClock.h"
#include "GameTime.h"

#include <chrono>
#include <vector>
#include "ParticleContactResolver.h"
#include "ParticleContactGenerator.h"
#include "ParticleForceGenerator.h"

namespace Annulus
{
	class Settings;
	class Particle;

	/**
	* A class which manages all physics entities for the particle physics engine.
	*/
	class ParticleWorld
	{
	public:
		/**
		* Constructor.
		* @param settings The settings for the world which are used to be used by it to perform update of all of its contained bodies.
		*/
		ParticleWorld(Settings& settings);
		/**
		* Destructor.
		* Destroys and frees the memory allocated to any physics simulation objects in the world.s
		*/
		~ParticleWorld();
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
		* Unregister the particle from the world.
		* @param particle The particle that needs to be unregistered.
		*/
		void UnregisterParticle(Particle& particle);
		/**
		* Register the particle force generator from the world.
		* @param particleForceGenerator The particle force generator that needs to be registered.
		*/
		void RegisterParticleForceGenerator(ParticleForceGenerator& particleForceGenerator);
		/**
		* Unregister the particle force generator from the world.
		* @param particleForceGenerator The particle force generator that needs to be unregistered.
		*/
		void UnregisterParticleForceGenerator(ParticleForceGenerator& particleForceGenerator);
		/**
		* Register the particle contact generator from the world.
		* @param particleContactGenerator The particle contact generator that needs to be registered.
		*/
		void RegisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator);
		/**
		* Unregister the particle contact generator from the world.
		* @param particleContactGenerator The particle contact generator that needs to be unregistered.
		*/
		void UnregisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator);
	private:
		/**
		* Calls UpdateForce for all the force generators, on all other their associated particles.
		* @param seconds The amount of time in seconds taken since the previous frame to execute.
		*/
		void UpdateForces(std::float_t seconds);
		/**
		* Clears the memory taken by various objects queued for deletion.
		*/
		void ClearDeleteQueues();
		/**
		* Generate the contacts with respect to the registered contact generators to this world.
		*/
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
		* The list of particle contacts which are assembled in each update.
		*/
		ParticleContact* mContacts;
		/**
		* The particle contact resolver associated with this world. Created on contruction of the world.
		*/
		ParticleContactResolver* mParticleContactResolver;

		/**
		* A vector of particles present in this world.
		*/
		std::vector<Particle*> mParticles;
		/**
		* A vector of particles that needs to be deleted.
		*/
		std::vector<Particle*> mParticlesDelete;
		/**
		* The vector of particle force generators registered to the world.
		*/
		std::vector<ParticleForceGenerator*> mParticleForceGenerators;
		/**
		* A vector of particle force generators that needs to be deleted.
		*/
		std::vector<ParticleForceGenerator*> mParticleForceGeneratorsDelete;
		/**
		* The vector of particle contact generators registered to the world.
		*/
		std::vector<ParticleContactGenerator*> mParticleContactGenerators;
		/**
		* A vector of particle contact generators that needs to be deleted.
		*/
		std::vector<ParticleContactGenerator*> mParticleContactGeneratorsDelete;
	};
}