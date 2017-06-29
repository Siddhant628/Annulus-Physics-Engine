#include "pch.h"
#include "ParticleCable.h"
#include "ParticleContact.h"
#include "Particle.h"

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	ParticleCable::ParticleCable(Particle& particle1, Particle& particle2):
		ParticleLink(particle1, particle2), mMaxLength(0), mRestitution(1)
	{

	}

	void ParticleCable::SetRestitution(std::float_t restitution)
	{
		mRestitution = restitution;
	}

	void ParticleCable::SetMaxLength(std::float_t length)
	{
		mMaxLength = length;
	}

	std::uint32_t ParticleCable::AddContact(ParticleContact* contacts, std::uint32_t limit) const
	{
		assert(limit > 0);

		std::uint32_t returnValue = 0;

		std::float_t length = CurrentLength();
		// Add contact if the cable is stretched.
		if(length > mMaxLength)
		{
			contacts->mParticle[0] = mParticle[0];
			contacts->mParticle[1] = mParticle[1];

			// Calculate the normal vector.
			glm::vec2 normal = mParticle[1]->GetPosition() - mParticle[0]->GetPosition();
			contacts->mContactNormal = glm::normalize(normal);

			// Assign other contact information.
			contacts->mPenetration = length - mMaxLength;
			contacts->mRestitution = mRestitution;

			// Return 1 as the count of contacts provided as output parameter.
			returnValue = 1;
		}
		return returnValue;
	}
}
