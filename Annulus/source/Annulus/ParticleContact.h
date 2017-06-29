#pragma once

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class Particle;
	/**
	* Represents a contact between two particles which needs to be handled by the contact resolver.
	* The contact resolver would apply appropriate impulses to the particles to resolve the contacts.
	*/
	class ParticleContact
	{
	public:
		/**
		* Resloves this contact for both velocity and interpenetration.
		* @seconds The amount of time for this frame.
		*/
		void Resolve(std::float_t seconds) const;
	private:
		/**
		* Resloves this contact for both velocity.
		* @seconds The amount of time for this frame.
		*/
		void ResolveVelocity(std::float_t seconds) const;
		/**
		* Resloves this contact for interpenetration.
		* @seconds The amount of time for this frame.
		*/
		void ResolveInterpenetration(std::float_t seconds) const;
		/**
		* Get the separating velocity at this contact.
		*/
		std::float_t CalculateSeparatingVelocity() const;
		/**
		* The particles which are requiring contact resolution.
		*/
		Particle* mParticle[2];
		/**
		* The coefficient of restitution for this specific collision.
		*/
		std::float_t mRestitution;
		/**
		* The direction of contact between two particles. This is a vector for particle 1 relative to particle 2.
		*/
		glm::vec2 mContactNormal;
	};
}