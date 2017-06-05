#include "pch.h"
#include "Settings.h"

using namespace  std::chrono;

namespace Annulus
{
	const std::int32_t Settings::sTimeFor30FPS = 33;
	const std::int32_t Settings::sTimeFor60FPS = 16;

	const glm::vec2 Settings::sDefaultGravity = glm::vec2(0.0f, -10.0f);

	Settings::Settings(std::chrono::milliseconds timeStep /* = std::chrono::milliseconds(sTimeFor60FPS) */, glm::vec2 gravity /* = glm::vec2(0.0f, -10.0f) */) : mTimeStep(timeStep), mGravity(gravity)
	{

	}

	const std::chrono::milliseconds& Settings::GetTimeStep() const
	{
		return  mTimeStep;
	}

	void Settings::SetTimeStep(const std::uint32_t updateRate)
	{
		assert(updateRate == 30 || updateRate == 60);

		if(updateRate == 30)
		{
			mTimeStep = std::chrono::milliseconds(33);	// 33 milliseconds correspond to 30 updates per second.
		}
		else if(updateRate == 60)
		{
			mTimeStep = std::chrono::milliseconds(16);	// 16 milliseconds correspond to 60 updates per second.
		}
	}

	const glm::vec2& Settings::GetGravity() const
	{
		return  mGravity;
	}

	void Settings::SetGravity(const glm::vec2& gravity)
	{
		mGravity = gravity;
	}
}
