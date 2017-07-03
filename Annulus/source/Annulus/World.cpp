#include "pch.h"
#include "World.h"
#include "Settings.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "ParticleContactGenerator.h"
#include "ParticleContact.h"

#include <iostream>

using namespace std::chrono;

namespace Annulus
{
	World::World(Settings& settings) : mSettings(&settings), mTimeSinceLastUpdate(nanoseconds(0)), mParticleContactResolver(nullptr)
	{
		ParticleContactGenerator::Initialize(*this);

		mParticleContactResolver = new ParticleContactResolver(*this);		
		// Allocate memory for contacts equivalent to the maximum contacts the world is allowed to handle.
		mContacts = new ParticleContact[mSettings->mMaxContacts];
	}

	World::~World()
	{
		// Destroy all particles
		auto end = mParticles.end();
		for(auto it = mParticles.begin(); it != end; ++it)
		{
			delete (*it);
		}
		// Destroy all particle contact generators.
		for (auto it = mParticleContactGenerators.begin(); it != mParticleContactGenerators.end(); ++it)
		{
			delete *it;
		}
		// Delete memory taken by this world.
		delete mParticleContactResolver;
		delete[] mContacts;
	}

	void World::Update(std::chrono::nanoseconds nanoseconds)
	{
		mTimeSinceLastUpdate += nanoseconds;

		if( mTimeSinceLastUpdate > mSettings->GetTimeStep())
		{
			std::float_t seconds = mTimeSinceLastUpdate.count() / 1000000000.0f;
			// Update Forces
			ParticleForceGenerator::UpdateForces(seconds);
			
			// Integrate
			auto end = mParticles.end();
			for (auto it = mParticles.begin(); it != end; ++it)
			{
				(*it)->Integrate(seconds);
			}

			// Generate Contacts
			std::uint32_t usedContacts = GenerateContacts();
			
			// Process Contacts
			if(usedContacts)
			{
				// TODO Case of calculate iterations boolean
				mParticleContactResolver->SetIterations(usedContacts * 2);
				mParticleContactResolver->ResolveContacts(mContacts, usedContacts, seconds);
			}

			mTimeSinceLastUpdate = std::chrono::nanoseconds(0);
		}
		ClearDeleteQueues();
	}

	Particle* World::CreateParticle()
	{
		Particle* newParticle = new Particle();
		mParticles.push_back(newParticle);
		return newParticle;
	}

	const Settings& World::GetSettings() const
	{
		return *mSettings;
	}

	const std::vector<Particle*>& World::GetParticles() const
	{
		return mParticles;
	}

	void World::RegisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator)
	{
		mParticleContactGenerators.push_back(&particleContactGenerator);
	}

	void World::UnregisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator)
	{
		mParticleContactGeneratorsDelete.push_back(&particleContactGenerator);
	}

	void World::ClearDeleteQueues()
	{
		// Clear the memory of obselete particle contact generators.
		std::vector<ParticleContactGenerator*>::iterator end = mParticleContactGeneratorsDelete.end();
		for (auto it = mParticleContactGeneratorsDelete.begin(); it != end; ++it)
		{
			auto itDelete = std::find(mParticleContactGenerators.begin(), mParticleContactGenerators.end(), *it);
			mParticleContactGenerators.erase(itDelete);
		}
		mParticleContactGeneratorsDelete.clear();
	}

	std::uint32_t World::GenerateContacts()
	{
		std::uint32_t limit = mSettings->mMaxContacts;
		ParticleContact* contact = mContacts;

		for(auto it = mParticleContactGenerators.begin(); it != mParticleContactGenerators.end(); ++it)
		{
			std::uint32_t used = (*it)->AddContact(contact, limit);
			limit -= used;
			contact += used;

			// Break in case we run out of contacts.
			if (limit <= 0)
			{
				break;
			}
		}
		return mSettings->mMaxContacts - limit;
	}
}