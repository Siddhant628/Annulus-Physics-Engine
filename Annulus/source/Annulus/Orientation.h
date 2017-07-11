#pragma once

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	/**
	* Represents the orientation of a RigidBody in the world.
	*/
	class Orientation final
	{
		friend class RigidBody;
	public:
		/**
		* Constructor.
		* @param orientation A vector with cosine and sine of the orientation, defaulted to theta = 0, with cosine as 1 and sine as 0.
		*/
		Orientation(const glm::vec2& orientation = glm::vec2(1, 0));
		/**
		* Destructor.
		*/
		~Orientation() = default;
		/**
		* Get the orientation in degrees between [0,2pi)
		*/
		std::uint32_t GetOrientationDegrees();
		/**
		* Set the orientation in degrees between [0,2pi)
		* @param degrees The rotation to set in degres.
		*/
		void SetOrientationDegrees(std::uint32_t degrees);
		/**
		* Get this orientation as a vector of cosine and sine of the angle theta between this orientation and the positive x-axis.
		*/
		const glm::vec2 GetOrientationVector();
		/**
		* Set this orientation as a vector of cosine and sine of the angle theta between this orientation and the positive x-axis.
		* @param orientation The vector containing the orientation to set.
		*/
		void SetOrientationVector(const glm::vec2& orientation);
	private:
		/**
		* A vector whose x-component is the cosine of theta and y-component is sine of theta (Theta is the angle between this orientation and the positive x-axis).
		* The angle theta thus increase in the counterclockwise direction.
		*/
		glm::vec2 mOrientation;
		/**
		* The cached value of rotation for this orientation.
		*/
		std::float_t mCachedDegrees;
		/**
		* If the cached value of degrees needs to be updated.
		*/
		bool mDegreesNeedUpdate;
	};
}