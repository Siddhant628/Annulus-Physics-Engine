#pragma once
#include "ParticleLink.h"

namespace Annulus
{
	class ParticleCable final: public ParticleLink
	{
	public:
		/**
		* Constructor.
		* @param particle1 The first particle in the cable.
		* @param particle2 The second particle in the cable.
		*/
		ParticleCable(Particle& particle1, Particle& particle2);
		/**
		* Set the value of restitution for this cable.
		* @param restitution The restitution value that should be set.
		*/
		void SetRestitution(std::float_t restitution);
		/**
		* Set the maximum length for this cable.
		* @param length The length to set for the cable.
		*/
		void SetMaxLength(std::float_t length);
		/**
		* Provides the contacts which are to be resolved as an output parameter.
		* @param contacts The set of contacts that need to be resolved (output).
		* @param limit Maximum number of contacts that can be written to.
		* @return The number of contacts which did get some data written into them.
		*/
		virtual std::uint32_t AddContact(ParticleContact* contacts, std::uint32_t limit) const override;
	private:
		/**
		* The maximum length this particle cable can have.
		*/
		std::float_t mMaxLength;
		/**
		* The coefficient of restitution for resolving this contact.
		*/
		std::float_t mRestitution;
	};
}
