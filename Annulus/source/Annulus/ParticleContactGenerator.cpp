#include "pch.h"
#include "ParticleContactGenerator.h"
#include "World.h"

namespace Annulus
{
	World* ParticleContactGenerator::sOwnerWord = nullptr;

	void ParticleContactGenerator::Initialize(World& world)
	{
		sOwnerWord = &world;
	}

	ParticleContactGenerator::~ParticleContactGenerator()
	{
		sOwnerWord->UnregisterParticleContactGenerator(*this);
	}

	ParticleContactGenerator::ParticleContactGenerator()
	{
		assert(sOwnerWord != nullptr);
		sOwnerWord->RegisterParticleContactGenerator(*this);
	}
}
