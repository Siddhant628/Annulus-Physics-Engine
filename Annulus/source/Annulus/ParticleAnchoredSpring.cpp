#include "pch.h"
#include "ParticleAnchoredSpring.h"

#include "Particle.h"

namespace Annulus
{
	ParticleAnchoredSpring::ParticleAnchoredSpring(Particle& particle)
	{
		mParticleList.push_back(&particle);
	}

	void ParticleAnchoredSpring::UpdateForce(Particle& particle, std::float_t seconds)
	{
		seconds;
		assert(&particle == mParticleList[0]);

		// Calculate the vector of the spring
		glm::vec2 force;
		force = particle.GetPosition();
		force -= mAnchor;

		// Calculate the magnitude of the spring
		std::float_t magnitude = static_cast<std::float_t>(glm::length(force));

		magnitude = magnitude - mRestLength;
		magnitude *= mSpringConstant;

		// Calculate the force to apply
		force = glm::normalize(force);
		force *= -magnitude;

		particle.AddForce(force);
	}

	void ParticleAnchoredSpring::SetRestLength(const std::float_t& restLength)
	{
		mRestLength = restLength;
	}

	void ParticleAnchoredSpring::SetSpringConstant(const std::float_t& springConstant)
	{
		mSpringConstant = springConstant;
	}

	void ParticleAnchoredSpring::SetAnchorPoint(const glm::vec2& anchorPoint)
	{
		mAnchor = anchorPoint;
	}
}