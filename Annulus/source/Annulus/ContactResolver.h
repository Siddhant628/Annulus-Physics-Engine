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
		/**
		* Set the number of iterations that the position resolution may use.
		* @param iterations The number of iterations.
		*/
		void SetPositionIterations(std::uint32_t iterations);
		/**
		* Set the number of iterations that the velocity resolution may use.
		* @param iterations The number of iterations.
		*/
		void SetVelocityIterations(std::uint32_t iterations);
	private:
		/**
		* Calculates and caches the data associated with contacts which is required for resolution of contacts when resolving both velocity and interpenetration.
		* @param contacts The contacts which require preparation of their contact data.
		* @param seconds The amount of time which has passed in previous frame.
		*/
		void PrepareContacts(const std::vector<const Contact*>& contacts, std::float_t seconds);
		/**
		* Resolve the interpenetration of contacts.
		* @param contacts The contacts which require resolution.
		*/
		void AdjustContacts(const std::vector<const Contact*>& contacts);
		/**
		* The number of iterations that the position resolution may use.
		*/
		std::uint32_t mPositionIterations;
		/**
		* The number of iterations that the velocity resolution may use.
		*/
		std::uint32_t mVelocityIterations;
		/**
		* The margin of error allowed in position resolution.
		*/
		const static std::float_t sPositionEpsilion;
	};
}
