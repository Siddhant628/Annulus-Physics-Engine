#include "pch.h"
#include "Circle.h"

namespace Annulus
{
	Circle::Circle(const RigidBody& body, std::float_t radius) : Collider(body), mRadius(radius)
	{
		mColliderType = ColliderType::Circle;
	}
}
