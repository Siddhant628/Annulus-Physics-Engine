#include "pch.h"
#include "World.h"
#include "Settings.h"

#include <iostream>

using namespace std::chrono;

namespace Annulus
{
	World::World(Settings& settings) : mSettings(&settings)
	{

	}

	void World::Update(std::chrono::nanoseconds nanoseconds)
	{
		mTimeSinceLastUpdate += nanoseconds;

		if( mTimeSinceLastUpdate > mSettings->GetTimeStep())
		{
			mTimeSinceLastUpdate = std::chrono::nanoseconds(0);
		}
	}
}