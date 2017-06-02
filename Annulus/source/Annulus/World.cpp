#include "pch.h"
#include "World.h"
#include "Settings.h"

#include <iostream>

using namespace std::chrono;

namespace Annulus
{
	World::World(Settings& settings) : mSettings(&settings), count(0)
	{

	}

	void World::Update(std::chrono::milliseconds milliseconds)
	{
		milliseconds;
		clock.UpdateGameTime(time);
		
		if( (high_resolution_clock::now() - mLastUpdate ) > mSettings->GetTimeStep())
		{
			++count;
			std::cout << "Frame: " << count << "  Elapsed Time: " << time.ElapsedGameTime().count() << "  Total time: " <<time.TotalGameTime().count() << std::endl;
			mLastUpdate = high_resolution_clock::now();

		}
	}
}
