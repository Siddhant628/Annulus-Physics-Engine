#include "pch.h"
#include "ParticleContact.h"
#include "Particle.h"

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	void ParticleContact::Resolve(std::float_t seconds) const
	{
		ResolveVelocity(seconds);
		ResolveInterpenetration(seconds);
	}

	ParticleContact::ParticleContact(Particle* particle1, Particle* particle2, std::float_t restitution, std::float_t penetration, const glm::vec2& contactNormal) :
		mParticle{ particle1, particle2 },
		mRestitution(restitution),
		mPenetration(penetration),
		mContactNormal(contactNormal)
	{

	}

	// TODO Check if the order of execution is affecting GetAcceleration() call.
	void ParticleContact::ResolveVelocity(std::float_t seconds) const
	{
		std::float_t separatingVelocity = CalculateSeparatingVelocity();

		// If the separating velocity is greater than 0, it means that we don't need to resolve this contact altogether since the particles are diverging.
		if (separatingVelocity <= 0)
		{
			// Calculate the separating velocity after the collision.
			std::float_t newSeparatingVelocity = -separatingVelocity * mRestitution;


			// Estimate the velocity build up just because of acceleration.
			glm::vec2 accelerationCausedVelocity = mParticle[0]->GetAcceleration();
			if (mParticle[1])
			{
				accelerationCausedVelocity -= mParticle[1]->GetAcceleration();
			}
			std::float_t accelerationCausedSeparatingVelocity = glm::dot(accelerationCausedVelocity, mContactNormal) * seconds;
			// If the separating velocity due to acceleration will lead to interpenetration, then remove its effect from the separating velocity.
			if (accelerationCausedSeparatingVelocity < 0)
			{
				newSeparatingVelocity += mRestitution * accelerationCausedSeparatingVelocity;
				if (newSeparatingVelocity < 0)
				{
					newSeparatingVelocity = 0;
				}
			}

			std::float_t deltaVelocity = newSeparatingVelocity - separatingVelocity;

			// Apply the change in velocity to each object in proportion to their inverse masses.
			std::float_t totalInverseMass = mParticle[0]->GetMassInverse();
			if (mParticle[1])
			{
				mParticle[1]->GetMassInverse();
			}
			// Proceed to resolving velocity only if both the particles aren't of infinite mass.
			if (totalInverseMass > 0)
			{
				std::float_t impulse = deltaVelocity / totalInverseMass;

				// Get the impulse as a vector along the contact normal since objects should be able to slide, etc.
				glm::vec2 impulsePerIMass = mContactNormal * impulse;

				// Change the velocities based on the impulse per unit inverse mass. (Resolution)
				mParticle[0]->SetVelocity(mParticle[0]->GetVelocity() + (impulsePerIMass * mParticle[0]->GetMassInverse()));
				if (mParticle[1] != nullptr)
				{
					mParticle[1]->SetVelocity(mParticle[1]->GetVelocity() + (impulsePerIMass * mParticle[1]->GetMassInverse()));
				}
			}
		}
	}

	void ParticleContact::ResolveInterpenetration(std::float_t seconds) const
	{
		seconds;
		// Resolve interpenetration only if there is penetration.
		if (mPenetration > 0)
		{
			std::float_t totalInverseMass = mParticle[0]->GetMassInverse();
			if (mParticle[1])
			{
				totalInverseMass += mParticle[1]->GetMassInverse();
			}
			// Resolve only if both the particles aren't of infinite mass.
			if (totalInverseMass > 0)
			{
				glm::vec2 movementPerIMass = mContactNormal * (mPenetration / totalInverseMass);

				// Update the positions in order to resolve interpenetrations. (Resolution)
				mParticle[0]->SetPosition(mParticle[0]->GetPosition() + (movementPerIMass * mParticle[0]->GetMassInverse()));
				if (mParticle[1] != nullptr)
				{
					mParticle[1]->SetPosition(mParticle[1]->GetPosition() + (movementPerIMass * mParticle[1]->GetMassInverse()));
				}

			}
		}
	}

	std::float_t ParticleContact::CalculateSeparatingVelocity() const
	{
		glm::vec2 relativeVelocity = mParticle[0]->GetVelocity();
		// Check if the particle is not in contact with a wall, etc.
		if (mParticle[1] != nullptr)
		{
			relativeVelocity -= mParticle[1]->GetVelocity();
		}
		return glm::dot(relativeVelocity, mContactNormal);
	}

	std::float_t ParticleContact::GetPenetration()
	{
		return mPenetration;
	}
}
