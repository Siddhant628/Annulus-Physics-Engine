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
		mTorqueAccumulator(0.0f)
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

	const std::float_t& RigidBody::GetRotation() const
	{
		return mRotation;
	}

	void RigidBody::SetRotation(std::float_t rotation)
	{
		mRotation = rotation;
	}

	const std::float_t& RigidBody::GetMassInverse() const
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

	const std::float_t& RigidBody::GetInertiaInverse() const
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

	void RigidBody::AddForce(const glm::vec2& force)
	{
		mForceAccumulator += force;
	}

	void RigidBody::AddForce(const glm::vec2& force, const glm::vec2& point)
	{
		// Account for force
		mForceAccumulator += force;
		// Account for torque
		glm::vec2 relativePosition = point - mPosition;
		mTorqueAccumulator += (relativePosition.x * force.y - relativePosition.y - force.x);
	}

	// TODO Implement
	void RigidBody::Integrate(std::float_t seconds)
	{
		if (mMassInverse > 0.0f)
		{

			mForceAccumulator = glm::vec2(0.0f, 0.0f);
		}
	}

	void RigidBody::Initialize(World& world)
	{
		assert(mOwnerWorld == nullptr);
		mOwnerWorld = &world;
	}
}