#pragma once
#include "ParticleForceGenerator.h"

namespace Annulus
{
	class World;

	class ParticleGravity : public ParticleForceGenerator
	{
	public:
		ParticleGravity(const World& world);

		void UpdateForce(Particle& particle, const std::float_t& seconds) override;
	private:
		const World* mWorld;
	};
}
