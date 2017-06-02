#pragma once

#include <chrono>

namespace Annulus
{
	class Settings
	{
	public:
		Settings();
		~Settings() = default;
	private:
		std::chrono::milliseconds mTimeStep;
	};
}