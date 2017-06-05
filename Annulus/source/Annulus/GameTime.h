#pragma once
#include <chrono>

#include "GameClock.h"

namespace Annulus
{
	class GameTime final
	{
	public:
		GameTime();

		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		void SetCurrentTime(const std::chrono::high_resolution_clock::time_point& currentTime);

		const std::chrono::nanoseconds& TotalGameTime() const;
		void SetTotalGameTime(const std::chrono::nanoseconds& totalGameTime);

		const std::chrono::nanoseconds& ElapsedGameTime() const;
		void SetElapsedGameTime(const std::chrono::nanoseconds& elapsedGameTime);

	private:
		std::chrono::high_resolution_clock::time_point mCurrentTime;
		std::chrono::nanoseconds mTotalGameTime;
		std::chrono::nanoseconds mElapsedGameTime;
	};
}
