#include "pch.h"
#include "World.h"

#include "Settings.h"
#include "RigidBody.h"
#include "ForceGenerator.h"
#include "Collider.h"
#include "CollisionDetector.h"

#include <chrono>

namespace Annulus
{
	World::World(const Settings& settings) :
		mSettings(&settings),
		mTimeSinceLastUpdate(std::chrono::nanoseconds(0))
	{
		mCollisionDetector = new CollisionDetector();

		RigidBody::Initialize(*this);
		ForceGenerator::Initialize(*this);
		Collider::Initialize(*this);
		mCollisionDetector->Initialize(*this);
	}

	World::~World()
	{
		ClearDeleteQueues();
		// Destroy all the rigid bodies.
		for (auto it = mBodies.begin(); it != mBodies.end(); ++it)
		{
			delete (*it);
		}
		// Destroy all the force generators.
		for (auto it = mForceGenerators.begin(); it != mForceGenerators.end(); ++it)
		{
			delete (*it);
		}
		// Destroy all the colliders.
		for (auto it = mColliders.begin(); it != mColliders.end(); ++it)
		{
			delete (*it);
		}
		// Destroy other members on heap.
		delete mCollisionDetector;
	}

	void World::Update(std::chrono::nanoseconds nanoseconds)
	{
		mTimeSinceLastUpdate += nanoseconds;

		// Perform update only if the fixed time step has passed.
		if (mTimeSinceLastUpdate > mSettings->GetTimeStep())
		{
			std::float_t seconds = mTimeSinceLastUpdate.count() / 1000000000.0f;

			// Update forces
			for (auto forceGenerator : mForceGenerators)
			{
				forceGenerator->UpdateForce(seconds);
			}
			// Integrate
			for (auto body : mBodies)
			{
				body->Integrate(seconds);
			}
			// Generate contacts
			mCollisionDetector->GenerateContacts(mColliders);

			// TODO Resolve contacts

			// Reset the time since last update.
			mTimeSinceLastUpdate = std::chrono::nanoseconds(0);
			// Remove pointers to entities no longer in this simulation.
			ClearDeleteQueues();
		}
	}

	const Settings& World::GetSettings() const
	{
		return *mSettings;
	}

	void World::RegisterBody(RigidBody& body)
	{
		mBodies.push_back(&body);
	}

	void World::UnregisterBody(RigidBody& body)
	{
		mBodiesDelete.push_back(&body);
	}

	void World::RegisterForceGenerator(ForceGenerator& generator)
	{
		mForceGenerators.push_back(&generator);
	}

	void World::UnregisterForceGenerator(ForceGenerator& generator)
	{
		mForceGeneratorsDelete.push_back(&generator);
	}

	void World::RegisterCollider(const Collider& collider)
	{
		mColliders.push_back(&collider);
	}

	void World::UnregisterCollider(const Collider& collider)
	{
		mCollidersDelete.push_back(&collider);
	}

	std::vector<const Contact*>& World::GetContacts()
	{
		return mContacts;
	}

	void World::ClearDeleteQueues()
	{
		// Clear the pointers to the bodies which are out of scope.
		for (auto it = mBodiesDelete.begin(); it != mBodiesDelete.end(); ++it)
		{
			auto itDelete = std::find(mBodies.begin(), mBodies.end(), *it);
			mBodies.erase(itDelete);
		}
		mBodiesDelete.clear();
		// Clear the pointers to the force generators which are out of scope.
		for (auto it = mForceGeneratorsDelete.begin(); it != mForceGeneratorsDelete.end(); ++it)
		{
			auto itDelete = std::find(mForceGenerators.begin(), mForceGenerators.end(), *it);
			mForceGenerators.erase(itDelete);
		}
		mForceGeneratorsDelete.clear();
		// Clear the pointers to the colliders which are out of scope.
		for (auto it = mCollidersDelete.begin(); it != mCollidersDelete.end(); ++it)
		{
			auto itDelete = std::find(mColliders.begin(), mColliders.end(), *it);
			mColliders.erase(itDelete);
		}
		mCollidersDelete.clear();
	}
}