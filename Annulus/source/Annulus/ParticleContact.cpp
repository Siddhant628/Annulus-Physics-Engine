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

	void ParticleContact::ResolveVelocity(std::float_t seconds) const
	{
		seconds;
		std::float_t separatingVelocity = CalculateSeparatingVelocity();

		// If the separating velocity is greater than 0, it means that we don't need to resolve this contact altogether since the particles are diverging.
		if (separatingVelocity <= 0)
		{
			// Calculate the separating velocity after the collision.
			std::float_t newSeparatingVelocity = -separatingVelocity * mRestitution;
			std::float_t deltaVelocity = newSeparatingVelocity - separatingVelocity;

			// Apply the change in velocity to each object in proportion to their inverse masses.
			std::float_t totalInverseMass = mParticle[0]->GetMassInverse() + mParticle[1]->GetMassInverse();

			// Proceed to resolving velocity only if both the particles aren't of infinite mass.
			if (totalInverseMass > 0)
			{
				std::float_t impulse = deltaVelocity / totalInverseMass;

				// Get the impulse as a vector along the contact normal since objects should be able to slide, etc.
				glm::vec2 impulsePerIMass = mContactNormal * impulse;

				// Change the velocities based on the impulse per unit inverse mass.
				mParticle[0]->SetVelocity(mParticle[0]->GetVelocity() + (impulsePerIMass * mParticle[0]->GetMassInverse()));
				if (mParticle[1] != nullptr)
				{
					mParticle[1]->SetVelocity(mParticle[1]->GetVelocity() + (impulsePerIMass * mParticle[1]->GetMassInverse()));
				}
			}
		}
	}

	// TODO Implement
	void ParticleContact::ResolveInterpenetration(std::float_t seconds) const
	{
		seconds;
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
}
