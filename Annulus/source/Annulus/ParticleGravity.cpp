#include "pch.h"
#include "ParticleGravity.h"
#include "Particle.h"
#include "ParticleWorld.h"
#include "Settings.h"

namespace Annulus
{
	ParticleGravity::ParticleGravity(const ParticleWorld& world) : mWorld(&world)
	{

	}

	void ParticleGravity::UpdateForce(Particle& particle, std::float_t seconds)
	{
		seconds;
		std::float_t massInverse = particle.GetMassInverse();
		if (massInverse != 0)
		{
			particle.AddForce(mWorld->GetSettings().GetGravity() / particle.GetMassInverse());
		}
	}
}
