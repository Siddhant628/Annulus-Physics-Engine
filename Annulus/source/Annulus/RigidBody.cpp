#include "pch.h"
#include "RigidBody.h"

#include "World.h"


namespace Annulus
{
	World* RigidBody::mOwnerWorld = nullptr;

	RigidBody::RigidBody()
	{
		mOwnerWorld->RegisterBody(*this);
	}

	RigidBody::~RigidBody()
	{
		mOwnerWorld->UnregisterBody(*this);
	}

	void RigidBody::Initialize(World& world)
	{
		assert(mOwnerWorld == nullptr);
		mOwnerWorld = &world;
	}
}