#include "pch.h"
#include "World.h"

#include "Settings.h"
#include "RigidBody.h"

#include <chrono>

namespace Annulus
{
	World::World(const Settings& settings) :
		mSettings(&settings),
		mTimeSinceLastUpdate(std::chrono::nanoseconds(0))
	{
		RigidBody::Initialize(*this);
	}

	World::~World()
	{
		ClearDeleteQueues();
		// Destroy all the rigid bodies.
		auto end = mBodies.end();
		for (auto it = mBodies.begin(); it != end; ++it)
		{
			delete (*it);
		}
	}

	void World::Update(std::chrono::nanoseconds nanoseconds)
	{
		mTimeSinceLastUpdate += nanoseconds;

		// Perform update only if the fixed time step has passed.
		if (mTimeSinceLastUpdate > mSettings->GetTimeStep())
		{
			std::float_t seconds = mTimeSinceLastUpdate.count() / 1000000000.0f;
			
			for(auto body : mBodies)
			{
				body->Integrate(seconds);
			}

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

	void World::ClearDeleteQueues()
	{
		// Clear the pointers to the bodies which are out of scope.
		for (auto it = mBodiesDelete.begin(); it != mBodiesDelete.end(); ++it)
		{
			auto itDelete = std::find(mBodies.begin(), mBodies.end(), *it);
			mBodies.erase(itDelete);
		}
		mBodiesDelete.clear();
	}
}
