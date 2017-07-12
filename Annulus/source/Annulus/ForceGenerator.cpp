#include "pch.h"
#include "ForceGenerator.h"

#include "World.h"

namespace Annulus
{
	World* ForceGenerator::sOwnerWorld = nullptr;

	ForceGenerator::~ForceGenerator()
	{
		sOwnerWorld->UnregisterForceGenerator(*this);
	}

	ForceGenerator::ForceGenerator()
	{
		sOwnerWorld->RegisterForceGenerator(*this);
	}

	void ForceGenerator::Initialize(World& world)
	{
		assert(sOwnerWorld == nullptr);
		sOwnerWorld = &world;
	}
}