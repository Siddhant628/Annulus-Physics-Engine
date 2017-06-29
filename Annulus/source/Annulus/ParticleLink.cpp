#include "pch.h"
#include "ParticleLink.h"
#include "Particle.h"

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	ParticleLink::ParticleLink(Particle& particle1, Particle& particle2) :
		mParticle{&particle1, &particle2}
	{

	}

	std::float_t ParticleLink::CurrentLength() const
	{
		glm::vec2 relativePosition = mParticle[0]->GetPosition() - mParticle[1]->GetPosition();
		return glm::length(relativePosition);
	}
}
