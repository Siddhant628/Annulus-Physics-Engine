#include "pch.h"
#include "ParticleContactResolver.h"
#include "World.h"
#include "ParticleContact.h"

namespace Annulus
{
	void ParticleContactResolver::SetIterations(std::uint32_t iterations)
	{
		mIterations = iterations;
	}

	ParticleContactResolver::ParticleContactResolver(const World& world): mOwnerWorld(world), mIterations(10)
	{

	}

	void ParticleContactResolver::ResolveContacts(ParticleContact* contacts, std::uint32_t numContacts, std::float_t seconds)
	{
		std::uint32_t iterations = 0;

		while(iterations < mIterations)
		{
			// Find the contact with the minimum separating velocity.
			std::float_t max = std::numeric_limits<std::float_t>::max();
			std::uint32_t maxIndex = numContacts;

			for(std::uint32_t i = 0; i < numContacts; ++i)
			{
				std::float_t separatingVelocity = contacts[i].CalculateSeparatingVelocity();

				if(separatingVelocity < 0 || contacts[i].GetPenetration() > 0)
				{
					max = separatingVelocity;
					maxIndex = i;
				}
			}
			// Check if anything that requires resolving is left.
			if(maxIndex == numContacts)
			{
				break;
			}
			// Resolve this contact.
			contacts[maxIndex].Resolve(seconds);
			++iterations;
		}
	}
}
