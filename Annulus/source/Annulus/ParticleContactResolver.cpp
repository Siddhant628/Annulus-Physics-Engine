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

	void ParticleContactResolver::ResolveContacts(std::vector<ParticleContact*>& contacts, std::float_t seconds)
	{
		std::uint32_t iterations = 0;

		while(iterations < mIterations)
		{
			// Find the contact with the minimum separating velocity.
			std::float_t max = std::numeric_limits<std::float_t>::max();
			auto maxIterator = --contacts.end();

			for(auto it = contacts.begin(); it != contacts.end(); ++it)
			{
				std::float_t separatingVelocity = (*it)->CalculateSeparatingVelocity();

				if(separatingVelocity < 0 || (*it)->GetPenetration() > 0)
				{
					max = separatingVelocity;
					maxIterator = it;
				}
			}
			// Check if anything that requires resolving is left.
			if(maxIterator == contacts.end())
			{
				break;
			}
			// Resolve this contact.
			(*maxIterator)->Resolve(seconds);
			++iterations;
		}
	}
}
