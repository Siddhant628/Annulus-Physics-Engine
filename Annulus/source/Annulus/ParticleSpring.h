#pragma once
#include "ParticleForceGenerator.h"

namespace Annulus
{
	/**
	* A spring force generator which produces a spring force between two particles.
	*/
	class ParticleSpring : protected ParticleForceGenerator
	{
	public:
		/**
		* Constructor.
		* @param particle1 The first particle in the spring.
		* @param particle2 The second particle in the spring.
		*/
		ParticleSpring(Particle& particle1, Particle& particle2);
		/**
		* Destructor.
		*/
		~ParticleSpring() = default;
		/**
		* Update the force acting on a particle for this frame.
		* @param particle The particle on which the force needs to be applied.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		void UpdateForce(Particle& particle, std::float_t seconds) override;
		/**
		* Set the rest length for this spring force generator.
		* @param restLength The length to set.
		*/
		void SetRestLength(std::float_t restLength);
		/**
		* Set the spring constant for this spring force generator.
		* @param springConstant The spring constant value to set.
		*/
		void SetSpringConstant(std::float_t springConstant);
	private:
		/**
		* The length of the spring, i.e. the length at which no force is exerted on either of the particles.
		*/
		std::float_t mRestLength;
		/**
		* The spring constant for this spring.
		*/
		std::float_t mSpringConstant;
	};
}