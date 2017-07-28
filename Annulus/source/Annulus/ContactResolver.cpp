#include "pch.h"
#include "ContactResolver.h"

#include "Contact.h"
#include "Collider.h"

namespace Annulus
{
	const std::float_t ContactResolver::sPositionEpsilion = 0.01f;
	const std::float_t ContactResolver::sVelocityEpsilon = 0.01f;

	void ContactResolver::ResolveContacts(const std::vector<const Contact*>& contacts, std::float_t seconds)
	{
		std::uint32_t numberOfContacts = contacts.size();
		// Return if there are no contacts to resolve.
		if(numberOfContacts > 0)
		{
			PrepareContacts(contacts, seconds);
			AdjustPositions(contacts);
			AdjustVelocities(contacts, seconds);
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

	void ContactResolver::AdjustPositions(const std::vector<const Contact*>& contacts)
	{
		std::uint32_t iterationsUsed = 0;
		auto contactIt = contacts.end();
		std::float_t maxPenetration;

		glm::vec2 linearChange[2], angularChange[2];
		glm::vec2 deltaPosition;

		// Iteratively resolve interpenetrations in order of severity.
		while(iterationsUsed < mPositionIterations)
		{
			maxPenetration = sPositionEpsilion;
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
							const_cast<Contact*>(*it)->mPenetration += glm::dot((*it)->mLinearPositionChange[contactBody], (*it)->mContactNormal) * (contactBody ? 1 : -1);
							//std::cout << "New Penetration: " << (*it)->mPenetration << std::endl;
						}
					}
				}
			}
			++iterationsUsed;
		}
	}

	void ContactResolver::AdjustVelocities(const std::vector<const Contact*>& contacts, std::float_t seconds)
	{

		std::uint32_t iterationsUsed = 0;

		// Iteratively resolve interpenetrations in order of severity.
		while(iterationsUsed < mVelocityIterations)
		{
			std::float_t maxVelocity = sVelocityEpsilon;
			auto contactIt = contacts.end();

			// Find the contact with maximum closing velocity (i.e. maximum desired change).
			for(auto it = contacts.begin(); it != contacts.end(); ++it)
			{
				if((*it)->mDesiredDeltaVelocity > maxVelocity)
				{
					contactIt = it;
					maxVelocity = (*it)->mDesiredDeltaVelocity;
				}
			}
			// If no contact with closing velocity was found, break.
			if(contactIt == contacts.end())
			{
				break;
			}
			// Resolve the velocity for this contact.
			const_cast<Contact*>(*contactIt)->ResolveVelocity();

			// Update the desired delta velocities for the contacts which might have been affected.
			for(auto it = contacts.begin(); it != contacts.end(); ++it)
			{
				// Check for each body in this contact.
				for(std::uint32_t bodyIndex = 0; bodyIndex < 2; ++bodyIndex)
				{
					// Check against each body in the newly resolved contact.
					for(std::uint32_t resolvedContactIndex = 0; resolvedContactIndex < 2; ++resolvedContactIndex)
					{
						if (&(*it)->mColliders[bodyIndex]->GetBody() == &(*contactIt)->mColliders[resolvedContactIndex]->GetBody())
						{
							const auto& rotationChange = (*contactIt)->mRotationChange[resolvedContactIndex];
							const auto& relativePosition = (*it)->mRelativeContactPosition[bodyIndex];
							glm::vec2 velocityChange = (*contactIt)->mVelocityChange[resolvedContactIndex] + glm::vec2(-rotationChange * relativePosition.y, rotationChange * relativePosition.x);
							
							// Transpose the velocity change into world-coordinates.
							glm::vec2 temp = velocityChange;
							std::float_t cosine = glm::dot((*it)->mContactNormal, glm::vec2(1, 0));
							std::float_t sine = sqrt(1 - cosine * cosine);
							velocityChange.x = temp.x * cosine - temp.y * sine;
							velocityChange.y = temp.x * sine + temp.y * cosine;

							const_cast<Contact*>(*it)->mContactVelocity += velocityChange * (bodyIndex? -1.0f : 1.0f);
							const_cast<Contact*>(*it)->CalculateDesiredVelocityChange(seconds);
						}
					}
				}
			}
			++iterationsUsed;
		}
	}
}