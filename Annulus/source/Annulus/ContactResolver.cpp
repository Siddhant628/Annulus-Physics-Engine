#include "pch.h"
#include "ContactResolver.h"

namespace Annulus
{
	void ContactResolver::ResolveContacts(const std::vector<const Contact*>& contacts, std::float_t seconds)
	{
		seconds;
		std::uint32_t numberOfContacts = contacts.size();
		// Return if there are no contacts to resolve.
		if(numberOfContacts > 0)
		{
			// TODO Prepare contacts for resolving.

			// TODO Resolve Interpenetration.

			// TODO Resolve Velocity. 
		}
	}
}
