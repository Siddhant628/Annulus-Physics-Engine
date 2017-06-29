#include "pch.h"
#include "ParticleRod.h"
#include "Particle.h"
#include "ParticleContact.h"

namespace Annulus
{
	ParticleRod::ParticleRod(Particle& particle1, Particle& particle2) : ParticleLink(particle1, particle2), mLength(1)
	{

	}

	void ParticleRod::SetLength(std::float_t length)
	{
		mLength = length;
	}

	std::uint32_t ParticleRod::AddContact(ParticleContact* contacts, std::uint32_t limit) const
	{
		limit;
		std::uint32_t returnValue = 0;

		std::float_t length = CurrentLength();
		if (length != mLength)
		{
			contacts->mParticle[0] = mParticle[0];
			contacts->mParticle[1] = mParticle[1];

			// Calculate the normal vector.
			glm::vec2 normal = mParticle[1]->GetPosition() - mParticle[0]->GetPosition();
			normal = glm::normalize(normal);

			// Assign other contact information.
			if (length > mLength)
			{
				contacts->mContactNormal = normal;
				contacts->mPenetration = length - mLength;
			}
			else
			{
				contacts->mContactNormal = -normal;
				contacts->mPenetration = mLength - length;
			}
			contacts->mRestitution = 0;

			returnValue = 1;
		}
		return returnValue;
	}
}
