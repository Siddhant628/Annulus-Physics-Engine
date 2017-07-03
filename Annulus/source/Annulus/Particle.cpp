#include "pch.h"
#include "Particle.h"
#include "Settings.h"
#include "World.h"

#include <iostream>

namespace Annulus
{
	const std::float_t Particle::sDefaultDamping = 0.999f;
	const std::float_t Particle::sDefaultMassInverse = 1;

	World* Particle::sOwnerWorld = nullptr;

	Particle::Particle() : mMassInverse(sDefaultMassInverse), mDamping(sDefaultDamping)
	{
		assert(sOwnerWorld != nullptr);

	}

	void Particle::Initialize(World& world)
	{
		sOwnerWorld = &world;
	}

	Particle::~Particle()
	{
		sOwnerWorld->UnregisterParticle(*this);
	}

	std::float_t Particle::GetMassInverse() const
	{
		return mMassInverse;
	}

	void Particle::SetInverseMass(std::float_t inverseMass)
	{
		mMassInverse = inverseMass;
	}

	void Particle::SetMass(std::float_t mass)
	{
		// A particle cannot have 0 mass, it is practically impossible. Moreover, it isn't possible to solve for acceleration for such a particle.
		assert(mass != 0.0f);
		mMassInverse = 1 / mass;
	}

	void Particle::SetDamping(std::float_t damping)
	{
		// The damping factor ranges between 0 and 1 (exclusive of 1 since partically any particle will have some damping in its linear motion).
		assert(damping >= 0 && damping < 1);
		mDamping = damping;
	}

	void Particle::SetPosition(const glm::vec2& position)
	{
		mPosition = position;
	}

	const glm::vec2& Particle::GetPosition() const
	{
		return mPosition;
	}

	void Particle::SetVelocity(const glm::vec2& velocity)
	{
		mVelocity = velocity;
	}

	const glm::vec2& Particle::GetVelocity() const
	{
		return mVelocity;
	}

	void Particle::AddForce(const glm::vec2& force)
	{
		mForceAccumulator += force;
	}

	void Particle::DebugParticle()
	{
		std::cout << std::endl;
		std::cout << "Position: " << mPosition.x << " " << mPosition.y << std::endl;
		std::cout << "Velocity: " << mVelocity.x << " " << mVelocity.y << std::endl;
		std::cout << "Acceleration: " << mForceAccumulator.x * mMassInverse << " " << mForceAccumulator.y * mMassInverse << std::endl;
		std::cout << std::endl;
	}

	glm::vec2 Particle::GetAcceleration() const
	{
		return mAcceleration;
	}

	void Particle::Integrate(const std::float_t seconds)
	{
		// In case the mass isn't infinite, integrate.
		if(mMassInverse > 0.0f)
		{
			// Update position
			mPosition = mPosition + (mVelocity*seconds);

			// Estimate acceleration
			glm::vec2 acceleration = mForceAccumulator * mMassInverse;
			mAcceleration = acceleration;

			// Update velocity
			mVelocity += acceleration*seconds;
			mVelocity *= glm::pow(mDamping, seconds);

			DebugParticle();
			// Clear the forces
			mForceAccumulator = glm::vec2(0.0f, 0.0f);
		}
	}
}