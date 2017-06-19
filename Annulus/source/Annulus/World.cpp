#include "pch.h"
#include "World.h"
#include "Settings.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"

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
			std::float_t seconds = mTimeSinceLastUpdate.count() / 1000000000.0f;
			// Update particles
			ParticleForceGenerator::UpdateForces(seconds);
			auto end = mParticles.end();
			for (auto it = mParticles.begin(); it != end; ++it)
			{
				(*it)->Integrate(seconds);
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

	const Settings& World::GetSettings() const
	{
		return *mSettings;
	}
}