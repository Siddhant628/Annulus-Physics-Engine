#include "pch.h"
#include "Particle.h"

namespace Annulus
{
	const std::float_t Particle::sDefaultDamping = 0.999f;
	const std::float_t Particle::sDefaultMassInverse = 1;

	Particle::Particle() : mMassInverse(sDefaultMassInverse), mDamping(sDefaultDamping)
	{

	}

	const std::float_t& Particle::GetMassInverse() const
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
}
