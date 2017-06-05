#include "pch.h"
#include "GameTime.h"
#include <chrono>

using namespace std::chrono;

namespace Annulus
{
	GameTime::GameTime() : mCurrentTime(), mTotalGameTime(0), mElapsedGameTime(0)
	{

	}

	const high_resolution_clock::time_point& GameTime::CurrentTime() const
	{
		return mCurrentTime;
	}

	void GameTime::SetCurrentTime(const high_resolution_clock::time_point& currentTime)
	{
		mCurrentTime = currentTime;
	}

	const nanoseconds& GameTime::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void GameTime::SetTotalGameTime(const std::chrono::nanoseconds& totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	const nanoseconds& GameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(const std::chrono::nanoseconds& elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}
}