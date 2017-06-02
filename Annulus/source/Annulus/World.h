#pragma once

#include <chrono>

namespace Annulus
{
	class Settings;

	/**
	* A class which manages all physics entities.
	*/
	class World
	{
	public:
		World(const Settings& settings);

		~World() = default;

		void Update(std::chrono::milliseconds milliseconds);
	private:

	};
}