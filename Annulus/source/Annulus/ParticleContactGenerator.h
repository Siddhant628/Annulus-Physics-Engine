#pragma once
#include <cstdint>

namespace Annulus
{
	class ParticleContact;
	/**
	* An abstract class for any particle contact generator.
	*/
	class ParticleContactGenerator
	{
	public:
		/**
		* Provides the contacts which are to be resolved as an output parameter.
		* @param contacts The set of contacts that need to be resolved (output).
		* @param limit Maximum number of contacts that can be written to.
		* @return The number of contacts which did get some data written into them.
		*/
		virtual std::uint32_t AddContact(ParticleContact* contacts, std::uint32_t limit) const = 0;
	};
}