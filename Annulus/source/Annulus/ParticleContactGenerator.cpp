#include "pch.h"
#include "ParticleContactGenerator.h"
#include "ParticleWorld.h"

namespace Annulus
{
	ParticleWorld* ParticleContactGenerator::sOwnerWord = nullptr;

	void ParticleContactGenerator::Initialize(ParticleWorld& world)
	{
		sOwnerWord = &world;
	}

	ParticleContactGenerator::~ParticleContactGenerator()
	{
		assert(sOwnerWord != nullptr);
		sOwnerWord->UnregisterParticleContactGenerator(*this);
	}

	ParticleContactGenerator::ParticleContactGenerator()
	{
		assert(sOwnerWord != nullptr);
		sOwnerWord->RegisterParticleContactGenerator(*this);
	}
}
