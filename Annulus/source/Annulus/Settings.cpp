#include "pch.h"
#include "Settings.h"

using namespace  std::chrono;

namespace Annulus
{
	const glm::vec2 Settings::sDefaultGravity = glm::vec2(0.0f, -10.0f);

	Settings::Settings(DurationSixtiethsOfSecond timeStep /* = std::chrono::duration<std::uint32_t, std::ratio<1, 60>>(1) */, glm::vec2 gravity /* = glm::vec2(0.0f, -10.0f) */) : mTimeStep(timeStep), mGravity(gravity)
	{

	}

	const Settings::DurationSixtiethsOfSecond& Settings::GetTimeStep() const
	{
		return  mTimeStep;
	}

	void Settings::SetTimeStep(const std::uint32_t updateRate)
	{
		assert(updateRate == 30 || updateRate == 60);

		if(updateRate == 30)
		{
			mTimeStep = std::chrono::duration<std::uint32_t, std::ratio<1, 60>>(2);
		}
		else if(updateRate == 60)
		{
			mTimeStep = std::chrono::duration<std::uint32_t, std::ratio<1, 60>>(1);
		}
	}

	const glm::vec2& Settings::GetGravity() const
	{
		return  mGravity;
	}
}
