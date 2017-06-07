#include "pch.h"
#include "World.h"
#include "Settings.h"
#include "Particle.h"

#include <iostream>

using namespace std::chrono;

namespace Annulus
{
	World::World(Settings& settings) : mSettings(&settings), mTimeSinceLastUpdate(nanoseconds(0))
	{

	}

	World::~World()
	{
		// Destroy all particles
		auto end = mParticles.end();
		for(auto it = mParticles.begin(); it != end; ++it)
		{
			delete (*it);
		}
	}

	void World::Update(std::chrono::nanoseconds nanoseconds)
	{
		mTimeSinceLastUpdate += nanoseconds;

		if( mTimeSinceLastUpdate > mSettings->GetTimeStep())
		{
			// Update particles
			auto end = mParticles.end();
			for (auto it = mParticles.begin(); it != end; ++it)
			{
				(*it)->Integrate(mTimeSinceLastUpdate);
				(*it)->DebugParticle();
			}

			mTimeSinceLastUpdate = std::chrono::nanoseconds(0);
		}
	}

	Particle* World::CreateParticle()
	{
		Particle* newParticle = new Particle();
		mParticles.push_back(newParticle);
		return newParticle;
	}
}
