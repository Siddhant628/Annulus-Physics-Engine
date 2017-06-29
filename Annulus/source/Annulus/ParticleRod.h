#pragma once
#include "ParticleLink.h"

namespace Annulus
{
	class ParticleRod : public ParticleLink
	{
	public:
		/**
		* Constructor.
		* @param particle1 The first particle in the Rod.
		* @param particle2 The second particle in the Rod.
		*/
		ParticleRod(Particle& particle1, Particle& particle2);
		/**
		* Set the length of this rod.
		* @param length The length to set for this rod.
		*/
		void SetLength(std::float_t length);
		/**
		* Provides the contacts which are to be resolved as an output parameter.
		* @param contacts The set of contacts that need to be resolved (output).
		* @param limit Maximum number of contacts that can be written to.
		* @return The number of contacts which did get some data written into them.
		*/
		virtual std::uint32_t AddContact(ParticleContact* contacts, std::uint32_t limit) const override;
	private:
		/**
		* The length of the rod.
		*/
		std::float_t mLength;
	};
}