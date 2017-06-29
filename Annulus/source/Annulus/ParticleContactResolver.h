#pragma once
#include <vector>
#include "ParticleContact.h"

namespace Annulus
{
	class World;
	/**
	* The contact resolver routine for the particle contacts that are present in the game.
	*/
	class ParticleContactResolver
	{
		friend class World;
	public:
		/**
		* Set the number of iterations for this resolver.
		* @param iterations The number of iterations to set.
		*/
		void SetIterations(std::uint32_t iterations);
	private:
		/**
		* Constructor.
		* @param world A reference to the world creating this particle contact resolver.
		*/
		ParticleContactResolver(const World& world);
		/**
		* The routine to resolve a given list of particle contacts.
		* @param contacts An array of ParticleContacts which need to be resolved.
		* @param numContacts The number of contacts that need to be resolved.
		* @param seconds The amount of time which has passed in previous frame.
		*/
		void ResolveContacts(ParticleContact* contacts, std::uint32_t numContacts, std::float_t seconds);
		/**
		*
		*/
		const World& mOwnerWorld;
		/**
		* The number of iterations allowed to this contact resolver. Default value is 10.
		*/
		std::uint32_t mIterations;
	};
}
