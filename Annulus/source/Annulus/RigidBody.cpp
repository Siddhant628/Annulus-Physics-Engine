#include "pch.h"
#include "RigidBody.h"

#include "World.h"


namespace Annulus
{
	World* RigidBody::mOwnerWorld = nullptr;

	RigidBody::RigidBody() :
		mMassInverse(1),
		mRotation(0),
		mInertiaInverse(1),
		mLinearDamping(1.0f),
		mAngularDamping(1.0f),
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
		mOrientation = orientation;
	}

	const glm::vec2& RigidBody::GetVelocity() const
	{
		return mVelocity;
	}

	void RigidBody::SetVelocity(const glm::vec2& velocity)
	{
		mVelocity = velocity;
	}

	std::float_t RigidBody::GetRotation() const
	{
		return mRotation;
	}

	void RigidBody::SetRotation(std::float_t rotation)
	{
		mRotation = rotation;
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
		if (damping >= 0.0f && damping <= 0.0f)
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
		if (damping >= 0.0f && damping <= 0.0f)
		{
			mAngularDamping = damping;
		}
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
		mTorqueAccumulator += (relativePosition.x * force.y - relativePosition.y - force.x);
	}

	void RigidBody::Integrate(std::float_t seconds)
	{
		seconds;
		// Estimate the linear and angular accelerations.
		mCachedAcceleration = mForceAccumulator * mMassInverse;
		mCachedAngularAcceleration = mTorqueAccumulator * mInertiaInverse;

		// Update velocity and rotation and account for their drag.
		mVelocity += mCachedAcceleration * seconds;
		mVelocity *= glm::pow(mLinearDamping, seconds);
		
		mRotation += mCachedAngularAcceleration * seconds;
		mRotation *= glm::pow(mAngularDamping, seconds);

		// Update position and orientation
		mPosition += mVelocity*seconds;
		
		std::float_t orientation = static_cast<std::float_t>(mOrientation.GetOrientationDegrees());
		orientation += mRotation*seconds;
		mOrientation.SetOrientationDegrees(static_cast<std::uint32_t>(orientation));

		// Clear out the accumulators.
		mForceAccumulator = glm::vec2(0.0f, 0.0f);
		mTorqueAccumulator = 0.0f;
	}

	void RigidBody::Initialize(World& world)
	{
		assert(mOwnerWorld == nullptr);
		mOwnerWorld = &world;
	}
}