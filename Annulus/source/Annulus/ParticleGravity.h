#pragma once
#include "ParticleForceGenerator.h"

namespace Annulus
{
	class World;

	class ParticleGravity : public ParticleForceGenerator
	{
	public:
		/**
		* Constructor.
		* @param world A reference to the world for which this force generator is being created.
		*/
		ParticleGravity(const World& world);
		/**
		* Destructor.
		*/
		~ParticleGravity() = default;
		/**
		* Update the force acting on a particle for this frame.
		* @param particle The particle on which the force needs to be applied.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		void UpdateForce(Particle& particle, const std::float_t& seconds) override;
	private:
		/**
		* A pointer to the world for which this force generator operates.
		*/
		const World* mWorld;
	};
}