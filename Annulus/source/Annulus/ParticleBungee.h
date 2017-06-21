#pragma once
#include "ParticleForceGenerator.h"

namespace Annulus
{
	class ParticleBungee : protected ParticleForceGenerator
	{
	public:
		/**
		* Constructor.
		* @param particle1 The first particle in the bungee.
		* @param particle2 The second particle in the bungee.
		*/
		ParticleBungee(Particle& particle1, Particle& particle2);
		/**
		* Destructor.
		*/
		~ParticleBungee() = default;
		/**
		* Update the force acting on a particle for this frame.
		* @param particle The particle on which the force needs to be applied.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		void UpdateForce(Particle& particle, const std::float_t& seconds) override;
		/**
		* Set the rest length for this bungee force generator.
		* @param restLength The length to set.
		*/
		void SetRestLength(const std::float_t& restLength);
		/**
		* Set the spring constant for this bungee force generator.
		* @param springConstant The spring constant value to set.
		*/
		void SetSpringConstant(const std::float_t& springConstant);
	private:
		/**
		* The length of the bungee, i.e. the length at which no force is exerted on either of the particles.
		*/
		std::float_t mRestLength;
		/**
		* The spring constant for this bungee.
		*/
		std::float_t mSpringConstant;
	};
}
