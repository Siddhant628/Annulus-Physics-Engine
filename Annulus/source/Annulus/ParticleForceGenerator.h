#pragma once

#include <vector>

namespace Annulus
{
	class Particle;

	/**
	* A force generator applies forces of specific nature to a set of particles.
	*/
	class ParticleForceGenerator
	{
		friend class World;
	public:
		/**
		* Destructor.
		* Deregisters this force generator from the static manager.
		*/
		~ParticleForceGenerator();
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
		* Calls UpdateForce for all the force generators, on all other their associated particles.
		*/
		static void UpdateForces(std::float_t seconds);
		/**
		* The list of force generators maintained by the static manager.
		*/
		static std::vector<ParticleForceGenerator*> mForceGenerators;
	};
}