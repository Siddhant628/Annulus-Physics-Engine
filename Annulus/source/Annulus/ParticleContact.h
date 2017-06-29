#pragma once

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class Particle;
	class ParticleContactResolver;
	/**
	* Represents a contact between two particles which needs to be handled by the contact resolver.
	* The contact resolver would apply appropriate impulses to the particles to resolve the contacts.
	*/
	class ParticleContact
	{
		friend class ParticleCable;
		friend class ParticleRod;
		friend class World;
	public:
		/**
		* Resloves this contact for both velocity and interpenetration.
		* @seconds The amount of time for this frame.
		*/
		void Resolve(std::float_t seconds) const;
		/**
		* Get the separating velocity at this contact.
		*/
		std::float_t CalculateSeparatingVelocity() const;
		/**
		* Get the penetration associated with this contact.
		*/
		std::float_t GetPenetration();
	private:
		/**
		* Constructor.
		* @param particle1 The first particle in contact.
		* @param particle2 The second particle in contact.
		* @param restitution The coefficient of restitution for this contact.
		* @param penetration The penetration depth for this collision.
		* @param contactNormal The vector between the particles relative to particle1.
		*/
		ParticleContact(Particle* particle1 = nullptr, Particle* particle2 = nullptr, std::float_t restitution = 1.0f, std::float_t penetration = 0.0f, const glm::vec2& contactNormal = glm::vec2(0, 0));
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
		/**
		* The depth of penetration at the contact.
		*/
		std::float_t mPenetration;
	};
}