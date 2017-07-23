#pragma once
#include <vector>

namespace Annulus
{
	class Contact;
	/**
	* The contact resolver routine for the contacts that are present in the simulation.
	* It iterates over the contacts and resolved them for velocity and interpenetration by making use of impulsive forces and moment.
	*/
	class ContactResolver
	{
	public:
		ContactResolver() = default;
		/**
		* The routine to resolve a given vector of contacts.
		* @param contacts The vector of Contacts which need to be resolved.
		* @param seconds The amount of time which has passed in previous frame.
		*/
		void ResolveContacts(const std::vector<const Contact*>& contacts, std::float_t seconds);
	};
}
