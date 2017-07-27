#include "pch.h"
#include "RigidBody.h"

#include "World.h"

#include <cmath>
#include <iostream>

namespace Annulus
{
	World* RigidBody::mOwnerWorld = nullptr;

	RigidBody::RigidBody() :
		mMassInverse(1),
		mRotation(0),
		mInertiaInverse(1),
		mLinearDamping(0.0f),
		mAngularDamping(0.0f),
		mTorqueAccumulator(0.0f),
		mCachedAngularAcceleration(0.0f)
	{
		assert(mOwnerWorld != nullptr);
		mOwnerWorld->RegisterBody(*this);
	}

	RigidBody::~RigidBody()
	{
		assert(mOwnerWorld != nullptr);
		mOwnerWorld->UnregisterBody(*this);
	}

	const glm::vec2& RigidBody::GetPosition() const
	{
		return mPosition;
	}

	void RigidBody::SetPosition(const glm::vec2& position)
	{
		mPosition = position;
	}

	const Orientation& RigidBody::GetOrientation() const
	{
		return  mOrientation;
	}

	void RigidBody::SetOrientation(const Orientation& orientation)
	{
		mOrientation.SetOrientationVector(orientation.mOrientation);
	}

	const glm::vec2& RigidBody::GetVelocity() const
	{
		return mVelocity;
	}

	void RigidBody::SetVelocity(const glm::vec2& velocity)
	{
		mVelocity = velocity;
	}

	void RigidBody::AddVelocity(const glm::vec2& deltaVelocity)
	{
		mVelocity += deltaVelocity;
	}

	std::float_t RigidBody::GetRotation() const
	{
		return mRotation;
	}

	void RigidBody::SetRotation(std::float_t rotation)
	{
		mRotation = rotation;
	}

	void RigidBody::AddRotation(std::float_t deltaRotation)
	{
		mRotation += deltaRotation;
	}

	std::float_t RigidBody::GetMassInverse() const
	{
		return mMassInverse;
	}

	void RigidBody::SetMassInverse(std::float_t massInverse)
	{
		assert(massInverse >= 0);
		mMassInverse = massInverse;
	}

	void RigidBody::SetMass(std::float_t mass)
	{
		assert(mass > 0);
		mMassInverse = 1.0f / mass;
	}

	std::float_t RigidBody::GetInertiaInverse() const
	{
		return mInertiaInverse;
	}

	void RigidBody::SetInertiaInverse(std::float_t inertiaInverse)
	{
		assert(inertiaInverse >= 0);
		mInertiaInverse = inertiaInverse;
	}

	void RigidBody::SetInertia(std::float_t inertia)
	{
		assert(inertia > 0);
		mInertiaInverse = (1.0f / inertia);
	}

	std::float_t RigidBody::GetLinearDamping() const
	{
		return mLinearDamping;
	}

	void RigidBody::SetLinearDamping(std::float_t damping)
	{
		if (damping >= 0.0f && damping <= 1.0f)
		{
			mLinearDamping = damping;
		}
	}

	std::float_t RigidBody::GetAngularDamping() const
	{
		return mAngularDamping;
	}

	void RigidBody::SetAngularDamping(std::float_t damping)
	{
		if (damping >= 0.0f && damping <= 1.0f)
		{
			mAngularDamping = damping;
		}
	}

	const glm::vec2& RigidBody::GetLastFrameAccelerationLinear() const
	{
		return mCachedAcceleration;
	}

	void RigidBody::AddForce(const glm::vec2& force)
	{
		mForceAccumulator += force;
	}

	void RigidBody::AddForce(const glm::vec2& force, const glm::vec2& point)
	{
		// Account for force.
		mForceAccumulator += force;
		// Account for torque.
		glm::vec2 relativePosition = point - mPosition;
		// Essentially this is a cross product in 2D, the resultant should be along -ve or +ve z axis, so we can represent it as a scalar quantity. (Torque = Relative Position X Force)
		mTorqueAccumulator += (relativePosition.x * force.y - relativePosition.y * force.x);
	}

	void RigidBody::AddForceRelative(const glm::vec2& force, const glm::vec2& point)
	{
		// Account for force.
		mForceAccumulator += force;
		// Account for torque.
		// Essentially this is a cross product in 2D, the resultant should be along -ve or +ve z axis, so we can represent it as a scalar quantity. (Torque = Relative Position X Force)
		mTorqueAccumulator += (point.x * force.y - point.y * force.x);
	}

	void RigidBody::GetPointInWorldSpace(const glm::vec2& point, glm::vec2& outputPoint)
	{
		std::float_t angle = atan2(point.y, point.x);
		std::float_t cosine = cos(angle);
		std::float_t sine = sin(angle);
		std::float_t length = glm::length(point);

		outputPoint.x = mPosition.x + length * (mOrientation.mOrientation.x*cosine - mOrientation.mOrientation.y*sine);
		outputPoint.y = mPosition.y + length * (mOrientation.mOrientation.y*cosine + mOrientation.mOrientation.x*sine);
	}

	void RigidBody::Integrate(std::float_t seconds)
	{
		seconds;
		// Estimate the linear and angular accelerations.
		mCachedAcceleration = mForceAccumulator * mMassInverse;
		mCachedAngularAcceleration = mTorqueAccumulator * mInertiaInverse;

		// Update velocity and rotation and account for their drag.
		mVelocity += mCachedAcceleration * seconds;
		mVelocity *= glm::pow(1.0f - mLinearDamping, seconds);
		
		mRotation += mCachedAngularAcceleration * seconds;
		mRotation *= glm::pow(1.0f - mAngularDamping, seconds);

		// Update position and orientation
		mPosition += mVelocity*seconds;
		mOrientation.TransformByDegrees(mRotation*seconds);
		
		// Clear out the accumulators.
		mForceAccumulator = glm::vec2(0.0f, 0.0f);
		mTorqueAccumulator = 0.0f;

		//DebugRigidBody();
	}

	void RigidBody::Initialize(World& world)
	{
		mOwnerWorld = &world;
	}

	void RigidBody::DebugRigidBody()
	{
		std::cout << std::endl;
		std::cout << "Position: X = " << mPosition.x << " Y = " << mPosition.y << std::endl;
		std::cout << "Velocity: " << mVelocity.x << " " << mVelocity.y << std::endl;
		std::cout << "Acceleration: X = " << mCachedAcceleration.x << " Y = " << mCachedAcceleration.y << std::endl;
		std::cout << "Orientation: " << mOrientation.GetOrientationDegrees() << std::endl;
		std::cout << "Angular Velocity: " << mRotation << std::endl;
		std::cout << "Angular Acceleration: " << mCachedAngularAcceleration << std::endl;
		std::cout << std::endl;
	}
}