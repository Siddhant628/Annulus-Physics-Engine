#include "pch.h"
#include "Orientation.h"

#include <cmath>
#define PI 3.14159265359f

namespace Annulus
{
	Orientation::Orientation(const glm::vec2& orientation) :
		mOrientation(glm::normalize(orientation)),
		mCachedDegrees(0.0f),
		mDegreesNeedUpdate(false)
	{

	}

	std::uint32_t Orientation::GetOrientationDegrees()
	{
		std::float_t valueToReturn = -1;

		if (mDegreesNeedUpdate) 
		{
			// Normalize the vector to minimize errors.
			mOrientation = glm::normalize(mOrientation);
			// Get the angle theta in radians between [-pi/2, pi/2] .
			float angle = asin(mOrientation.y);
			// Convert the angle to degrees.
			angle = angle * (180.0f / PI);
			// Convert the angle value to [0, 2pi].
			// In case the angle is in first two quadrants.
			if (mOrientation.y > 0)
			{
				if (mOrientation.x > 0)
				{
					valueToReturn = angle;
				}
				else if (mOrientation.x < 0)
				{
					valueToReturn = 180 - angle;
				}
			}
			// In case the angle is in last two quadrants.
			else if (mOrientation.y < 0)
			{
				if (mOrientation.x < 0)
				{
					valueToReturn = 180 - angle;
				}
				else if (mOrientation.x > 0)
				{
					valueToReturn = 360 + angle;
				}
			}
			// In case the sine of angle is 0.
			else
			{
				if (mOrientation.x > 0)
				{
					valueToReturn = 0;
				}
				else
				{
					valueToReturn = 180;
				}
			}
		}
		else
		{
			valueToReturn = mCachedDegrees;
		}
		assert(valueToReturn != -1);
		return static_cast<std::uint32_t>(valueToReturn);
	}

	void Orientation::SetOrientationDegrees(std::uint32_t degrees)
	{
		std::float_t radians = PI * degrees / 180.0f;
		mOrientation.x = cos(radians);
		mOrientation.y = sin(radians);
		mDegreesNeedUpdate = true;
	}

	const glm::vec2 Orientation::GetOrientationVector()
	{
		// Normalize the vector to minimize errors.
		mOrientation = glm::normalize(mOrientation);
		return mOrientation;
	}

	void Orientation::SetOrientationVector(const glm::vec2& orientation)
	{
		mOrientation = orientation;
		mDegreesNeedUpdate = true;
	}
}