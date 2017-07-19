#pragma once
#include "Collider.h"

namespace Annulus
{
	/**
	* A collider which is circular in shape.
	*/
	class Circle final: public Collider
	{
	public:
		/**
		* Constructor.
		* @param body The rigid body with which this collider is associated.
		* @param radius The radius of the circular collider.
		*/
		explicit Circle(const RigidBody& body, std::float_t radius);
		/**
		* Destructor.
		*/
		virtual ~Circle() = default;
	private:
		std::float_t mRadius;
	};
}
