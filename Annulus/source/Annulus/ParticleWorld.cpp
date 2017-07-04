#include "pch.h"
#include "ParticleWorld.h"
#include "Settings.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "ParticleContactGenerator.h"
#include "ParticleContact.h"

#include <iostream>

using namespace std::chrono;

namespace Annulus
{
	ParticleWorld::ParticleWorld(Settings& settings) : mSettings(&settings), mTimeSinceLastUpdate(nanoseconds(0)), mParticleContactResolver(nullptr)
	{
		Particle::Initialize(*this);
		ParticleForceGenerator::Initialize(*this);
		ParticleContactGenerator::Initialize(*this);

		mParticleContactResolver = new ParticleContactResolver(*this);		
		// Allocate memory for contacts equivalent to the maximum contacts the world is allowed to handle.
		mContacts = new ParticleContact[mSettings->mMaxContacts];
	}

	ParticleWorld::~ParticleWorld()
	{
		// Destroy all particles
		auto end = mParticles.end();
		for(auto it = mParticles.begin(); it != end; ++it)
		{
			delete (*it);
		}
		// Destroy all particle force generators.
		for(auto it = mParticleForceGenerators.begin(); it != mParticleForceGenerators.end(); ++it)
		{
			delete *it;
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

	void ParticleWorld::Update(std::chrono::nanoseconds nanoseconds)
	{
		mTimeSinceLastUpdate += nanoseconds;

		if( mTimeSinceLastUpdate > mSettings->GetTimeStep())
		{
			std::float_t seconds = mTimeSinceLastUpdate.count() / 1000000000.0f;
			// Update Forces
			UpdateForces(seconds);
			
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

	Particle* ParticleWorld::CreateParticle()
	{
		Particle* newParticle = new Particle();
		mParticles.push_back(newParticle);
		return newParticle;
	}

	const Settings& ParticleWorld::GetSettings() const
	{
		return *mSettings;
	}

	const std::vector<Particle*>& ParticleWorld::GetParticles() const
	{
		return mParticles;
	}

	void ParticleWorld::UnregisterParticle(Particle& particle)
	{
		mParticlesDelete.push_back(&particle);
	}

	void ParticleWorld::RegisterParticleForceGenerator(ParticleForceGenerator& particleForceGenerator)
	{
		mParticleForceGenerators.push_back(&particleForceGenerator);
	}

	void ParticleWorld::UnregisterParticleForceGenerator(ParticleForceGenerator& particleForceGenerator)
	{
		mParticleForceGeneratorsDelete.push_back(&particleForceGenerator);
	}

	void ParticleWorld::RegisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator)
	{
		mParticleContactGenerators.push_back(&particleContactGenerator);
	}

	void ParticleWorld::UnregisterParticleContactGenerator(ParticleContactGenerator& particleContactGenerator)
	{
		mParticleContactGeneratorsDelete.push_back(&particleContactGenerator);
	}

	void ParticleWorld::ClearDeleteQueues()
	{
		// Clear the memory of obselete particle force generators.
		for(auto it = mParticleForceGeneratorsDelete.begin(); it != mParticleForceGeneratorsDelete.end(); ++it)
		{
			auto itDelete = std::find(mParticleForceGenerators.begin(), mParticleForceGenerators.end(), *it);
			mParticleForceGenerators.erase(itDelete);
		}
		mParticleForceGeneratorsDelete.clear();

		// Clear the memory of obselete particle contact generators.
		for (auto it = mParticleContactGeneratorsDelete.begin(); it != mParticleContactGeneratorsDelete.end(); ++it)
		{
			auto itDelete = std::find(mParticleContactGenerators.begin(), mParticleContactGenerators.end(), *it);
			mParticleContactGenerators.erase(itDelete);
		}
		mParticleContactGeneratorsDelete.clear();

		// Clear the memory of obselete particles.
		for(auto it = mParticlesDelete.begin(); it != mParticlesDelete.end(); ++it)
		{
			auto itDelete = std::find(mParticles.begin(), mParticles.end(), *it);
			mParticles.erase(itDelete);
		}
		mParticlesDelete.clear();
	}

	std::uint32_t ParticleWorld::GenerateContacts()
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

	void ParticleWorld::UpdateForces(std::float_t seconds)
	{
		for (auto it = mParticleForceGenerators.begin(); it != mParticleForceGenerators.end(); ++it)
		{
			auto& particles = (*it)->mParticleList;

			for (auto iter = particles.begin(); iter != particles.end(); ++iter)
			{
				(*it)->UpdateForce(**iter, seconds);
			}
		}
	}
}
