#include "pch.h"
#include "World.h"
#include "Settings.h"

#include <chrono>

namespace Annulus
{
	World::World(const Settings& settings) :
		mSettings(&settings),
		mTimeSinceLastUpdate(std::chrono::nanoseconds(0))
	{

	}

	World::~World()
	{

	}

	void World::Update(std::chrono::nanoseconds nanoseconds)
	{
		mTimeSinceLastUpdate += nanoseconds;

		// Perform update only if the fixed time step has passed.
		if (mTimeSinceLastUpdate > mSettings->GetTimeStep())
		{
			std::float_t seconds = mTimeSinceLastUpdate.count() / 1000000000.0f;
			seconds;

			// Reset the time since last update.
			mTimeSinceLastUpdate = std::chrono::nanoseconds(0);
		}
	}

	const Settings& World::GetSettings() const
	{
		return *mSettings;
	}
}