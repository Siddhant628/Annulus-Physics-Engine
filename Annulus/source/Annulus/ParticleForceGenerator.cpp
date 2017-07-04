#include "pch.h"
#include "ParticleForceGenerator.h"
#include "ParticleWorld.h"

#include <algorithm>
#include <cassert>

namespace Annulus
{
	ParticleWorld* ParticleForceGenerator::sOwnerWorld = nullptr;

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

	void ParticleForceGenerator::Initialize(ParticleWorld& world)
	{
		sOwnerWorld = &world;
	}

	ParticleForceGenerator::ParticleForceGenerator()
	{
		assert(sOwnerWorld != nullptr);
		sOwnerWorld->RegisterParticleForceGenerator(*this);
	}

	ParticleForceGenerator::~ParticleForceGenerator()
	{
		assert(sOwnerWorld != nullptr);
		sOwnerWorld->UnregisterParticleForceGenerator(*this);
	}
}