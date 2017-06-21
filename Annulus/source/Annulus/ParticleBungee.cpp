#include "pch.h"
#include "ParticleBungee.h"

#include "Particle.h"

namespace Annulus
{
	ParticleBungee::ParticleBungee(Particle& particle1, Particle& particle2)
	{
		mParticleList.push_back(&particle1);
		mParticleList.push_back(&particle2);
	}

	void ParticleBungee::UpdateForce(Particle& particle, const std::float_t& seconds)
	{
		seconds;
		// Get the other particle
		assert(&particle == mParticleList[0] || &particle == mParticleList[1]);
		Particle* otherParticle = nullptr;
		if (mParticleList[0] == &particle)
		{
			otherParticle = mParticleList[1];
		}
		else
		{
			otherParticle = mParticleList[0];
		}

		// Calculate the vector of the spring
		glm::vec2 force;
		force = particle.GetPosition();
		force -= otherParticle->GetPosition();

		// Calculate the magnitude of force
		std::float_t magnitude = static_cast<std::float_t>(glm::length(force));
		// Return if the bungee is not streched
		if(magnitude <= mRestLength)
		{
			return;
		}

		magnitude = magnitude - mRestLength;
		magnitude *= mSpringConstant;

		// Calculate the force to apply
		force = glm::normalize(force);
		force *= -magnitude;

		particle.AddForce(force);
	}

	void ParticleBungee::SetRestLength(const std::float_t& restLength)
	{
		mRestLength = restLength;
	}

	void ParticleBungee::SetSpringConstant(const std::float_t& springConstant)
	{
		mSpringConstant = springConstant;
	}
}
