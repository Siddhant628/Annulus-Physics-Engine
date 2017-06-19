#include "pch.h"
#include "ParticleSpring.h"
#include "Particle.h"

#include <cmath>

namespace Annulus
{
	ParticleSpring::ParticleSpring(Particle& particle1, Particle& particle2) : mSpringConstant(1.0f), mRestLength(1.0f)
	{
		mParticleList.push_back(&particle1);
		mParticleList.push_back(&particle2);
	}

	void ParticleSpring::UpdateForce(Particle& particle, const std::float_t& seconds)
	{
		seconds;
		// Get the other particle
		Particle* otherParticle = nullptr;
		if(mParticleList[0] == &particle)
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
		
		magnitude = magnitude - mRestLength;
		magnitude *= mSpringConstant;

		// Calculate the force to apply
		force = glm::normalize(force);
		force *= -magnitude;

		particle.AddForce(force);
	}

	void ParticleSpring::SetRestLength(const std::float_t& restLength)
	{
		mRestLength = restLength;
	}

	void ParticleSpring::SetSpringConstant(const std::float_t& springConstant)
	{
		mSpringConstant = springConstant;
	}
}