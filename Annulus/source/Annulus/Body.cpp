#include "pch.h"
#include "Body.h"

namespace Annulus
{
	Body::Body() : mShape(nullptr), mRotation(0.0f), mAngularVelocity(0.0f), mTorque(0.0f), mMass(0.0f), mMassInverse(0.0f), mMomentOfInertia(0.0f), mMomentOfIntertiaInverse(0.0f)
	{
		
	}
}