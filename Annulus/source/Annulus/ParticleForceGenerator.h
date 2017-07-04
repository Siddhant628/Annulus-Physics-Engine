#pragma once

#include <vector>

namespace Annulus
{
	class ParticleWorld;
	class Particle;

	/**
	* A force generator applies forces of specific nature to a set of particles.
	*/
	class ParticleForceGenerator
	{
		friend class ParticleWorld;
	public:
		/**
		* Destructor.
		* Deregisters this force generator from the static manager.
		*/
		virtual ~ParticleForceGenerator();
		/**
		* Update the force acting on a particle for this frame.
		* @param particle The particle on which the force needs to be applied.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		virtual void UpdateForce(Particle& particle, std::float_t seconds) = 0;
		/**
		* Register a particle to this force generator. The force generator will apply force to this particle.
		* @param particle The particle to register.
		*/
		void RegisterParticle(Particle& particle);
		/**
		* Deregister a particle to this force generator. The force generator won't apply force to this particle.
		* @param particle The particle to deregister.
		*/
		void DeregisterParticle(Particle& particle);
		/**
		* Deregister all the particles associated with this particle force generator.
		*/
		void ClearParticles();
	protected:
		/**
		* Constructor.
		* Registers this force generator to the static manager.
		*/
		ParticleForceGenerator();
		/**
		* The list of particles on which this force generator applies forces.
		*/
		std::vector<Particle*> mParticleList;
	private:
		/**
		* The owner world with which this particle force generator is associated.
		*/
		static ParticleWorld* sOwnerWorld;

		/**
		* Initialize the world associated with all the particle force generators.
		* @param world The world which has to be made as the owner of all particle force generators.
		*/
		static void Initialize(ParticleWorld& world);
	};
}