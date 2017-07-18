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

	std::float_t Orientation::GetOrientationDegrees() const
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
				else
				{
					valueToReturn = 90;
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
				else
				{
					valueToReturn = 270;
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
			const_cast<std::float_t&>(mCachedDegrees) = valueToReturn;
			const_cast<bool&>(mDegreesNeedUpdate) = false;
		}
		else
		{
			valueToReturn = mCachedDegrees;
		}
		assert(valueToReturn != -1);
		return valueToReturn;
	}

	void Orientation::SetOrientationDegrees(std::float_t degrees)
	{
		assert(degrees >= 0 && degrees < 360);
		std::float_t radians = degrees * (PI / 180.0f);
		mOrientation.x = cos(radians);
		mOrientation.y = sin(radians);
		mCachedDegrees = degrees;
	}

	const glm::vec2 Orientation::GetOrientationVector() const
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

	void Orientation::TransformByDegrees(std::float_t degrees)
	{
		std::float_t cosine = mOrientation.x;
		std::float_t sine = mOrientation.y;
		std::float_t radians = degrees * (PI / 180.0f);
		// Update the orientaion.
		mOrientation.x = cosine * cos(radians) - sine * sin(radians);
		mOrientation.y = sine * cos(radians) + cosine * sin(radians);
		// Cache the rotation.
		mCachedDegrees += degrees;
		if(mCachedDegrees >= 360)
		{
			mCachedDegrees -= 360;
		}
		else if(mCachedDegrees < 0)
		{
			mCachedDegrees += 360;
		}
	}
}