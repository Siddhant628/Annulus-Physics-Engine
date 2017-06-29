#include "pch.h"
#include "ParticleForceGenerator.h"

#include <algorithm>
#include <cassert>

namespace Annulus
{
	std::vector<ParticleForceGenerator*> ParticleForceGenerator::mForceGenerators;

	void ParticleForceGenerator::RegisterParticle(Particle& particle)
	{
		mParticleList.push_back(&particle);
	}

	void ParticleForceGenerator::DeregisterParticle(Particle& particle)
	{
		auto it = std::find(mParticleList.begin(), mParticleList.end(), &particle);
		if(it != mParticleList.end())
		{
			mParticleList.erase(it);
		}
	}

	void ParticleForceGenerator::ClearParticles()
	{
		mParticleList.clear();
	}

	void ParticleForceGenerator::UpdateForces(std::float_t seconds)
	{
		for(auto it = mForceGenerators.begin(); it != mForceGenerators.end(); ++it)
		{
			auto& particles = (*it)->mParticleList;
			
			for( auto iter = particles.begin(); iter != particles.end(); ++iter)
			{
				(*it)->UpdateForce(**iter, seconds);
			}
		}
	}

	ParticleForceGenerator::ParticleForceGenerator()
	{
		mForceGenerators.push_back(this);
	}

	ParticleForceGenerator::~ParticleForceGenerator()
	{
		auto it = std::find(mForceGenerators.begin(), mForceGenerators.end(), this);
		assert(it != mForceGenerators.end());
		mForceGenerators.erase(it);
	}
}