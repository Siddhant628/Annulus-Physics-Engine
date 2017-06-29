#pragma once
#include "ParticleContactGenerator.h"

namespace Annulus
{
	class Particle;
	/**
	* Links are contacts which are formed by conntecting two particles. It forms basis for links such as cables or rods.
	*/
	class ParticleLink: public ParticleContactGenerator
	{
	public:
		/**
		* Constructor.
		* @param particle1 The first particle in the link.
		* @param particle2 The second particle in the link.
		*/
		ParticleLink(Particle& particle1, Particle& particle2);
		/**
		* Provides the contacts which are to be resolved as an output parameter.
		* @param contacts The set of contacts that need to be resolved (output).
		* @param limit Maximum number of contacts that can be written to.
		* @return The number of contacts which did get some data written into them.
		*/
		virtual std::uint32_t AddContact(ParticleContact* contacts, std::uint32_t limit) const = 0;
	protected:
		/**
		* The current length of the link.
		*/
		std::float_t CurrentLength() const;
		/**
		* The pointer to the pair of particles in the link.
		*/
		Particle* mParticle[2];

	};
}