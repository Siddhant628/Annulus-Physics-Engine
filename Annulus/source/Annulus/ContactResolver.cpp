#include "pch.h"
#include "ContactResolver.h"

#include "Contact.h"
#include "Collider.h"

namespace Annulus
{
	void ContactResolver::ResolveContacts(const std::vector<const Contact*>& contacts, std::float_t seconds)
	{
		std::uint32_t numberOfContacts = contacts.size();
		// Return if there are no contacts to resolve.
		if(numberOfContacts > 0)
		{
			PrepareContacts(contacts, seconds);
			AdjustContacts(contacts);

			// TODO Resolve Velocity. 
		}
	}

	void ContactResolver::SetPositionIterations(std::uint32_t iterations)
	{
		mPositionIterations = iterations;
	}

	void ContactResolver::SetVelocityIterations(std::uint32_t iterations)
	{
		mVelocityIterations = iterations;
	}

	void ContactResolver::PrepareContacts(const std::vector<const Contact*>& contacts, std::float_t seconds)
	{
		seconds;
		for(auto& contact : contacts)
		{
			const_cast<Contact*>(contact)->CalculateInternals(seconds);
		}
	}

	void ContactResolver::AdjustContacts(const std::vector<const Contact*>& contacts)
	{
		auto contactIt = contacts.end();
		std::float_t maxPenetration;
		std::uint32_t iterationsUsed = 0;

		glm::vec2 linearChange[2], angularChange[2];
		glm::vec2 deltaPosition;

		// Iteratively resolve interpenetrations in order of severity.
		while(iterationsUsed < mPositionIterations)
		{
			maxPenetration = 0.0f;
			contactIt = contacts.end();
			for(auto it = contacts.begin(); it != contacts.end(); ++it)
			{
				if((*it)->mPenetration >= maxPenetration)
				{
					contactIt = it;
					maxPenetration = (*it)->mPenetration;
				}
			}
			// If no contact with interpenetration was found, break.
			if(contactIt == contacts.end())
			{
				break;
			}
			// Resolve the interpenetration for this contact.
			const_cast<Contact*>(*contactIt)->ResolveInterpenetration();

			// Update the penetrations of those contacts which might have been affected by the resolution above.
			for(auto it = contacts.begin(); it != contacts.end(); ++it)
			{
				// Check for each body in the contact.
				for(std::uint32_t contactBody = 0; contactBody < 2; ++contactBody)
				{
					// Update penetration if any of the bodies in the contact was one of the bodies in the above resolution.
					for(std::uint32_t resolvedBody = 0; resolvedBody < 2; ++resolvedBody)
					{
						if(&(*it)->mColliders[contactBody]->GetBody() == &(*contactIt)->mColliders[resolvedBody]->GetBody())
						{
							const_cast<Contact*>(*it)->mPenetration += glm::dot((*it)->mLinearPositionChange[0] - (*it)->mLinearPositionChange[1], (*it)->mContactNormal) * (contactBody ? 1 : -1);
						}
					}
				}
			}
		}
	}
}
