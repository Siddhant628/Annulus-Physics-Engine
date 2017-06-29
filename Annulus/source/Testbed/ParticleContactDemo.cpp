#include "pch.h"
#include "ParticleContactDemo.h"
#include "Particle.h"
#include "World.h"
#include "ParticleRod.h"
#include "ParticleCable.h"
#include "ParticleGravity.h"

using namespace Annulus;

namespace Demos
{
	const glm::vec2 ParticleContactDemo::sParticlePosition1 = glm::vec2(-100.0f, 0.0f);
	const glm::vec2 ParticleContactDemo::sParticlePosition2 = glm::vec2(100.0f, 0.0f);

	ParticleContactDemo::ParticleContactDemo(sf::RenderWindow& renderWindow, Annulus::World& world) : Demo(renderWindow, world), mParticle1(nullptr), mParticle2(nullptr), mCircle1(nullptr), mCircle2(nullptr)
	{
	}

	ParticleContactDemo::~ParticleContactDemo()
	{

	}

	void ParticleContactDemo::Initialize()
	{
		// Create particles
		mParticle1 = mWorld.CreateParticle();
		mParticle1->SetPosition(sParticlePosition1);
		mParticle1->SetDamping(0.9f);
		mParticle1->SetMass(10.0f);
		

		mParticle2 = mWorld.CreateParticle();
		mParticle2->SetPosition(sParticlePosition2);
		mParticle2->SetDamping(0.9f);
		mParticle2->SetMass(10.0f);
		mParticle2->SetInverseMass(0);

		// Create circles to visualize particles
		mCircle1 = new sf::CircleShape(sParticleRadius);
		mCircle1->setPosition(0, 0);
		mCircle1->setFillColor(sf::Color::Black);

		mCircle2 = new sf::CircleShape(sParticleRadius);
		mCircle2->setPosition(0, 0);
		mCircle2->setFillColor(sf::Color::Black);

		ParticleRod* rod = new ParticleRod(*mParticle1, *mParticle2);
		rod->SetLength(200);

		//ParticleCable* cable = new ParticleCable(*mParticle1, *mParticle2);
		//cable->SetMaxLength(200);
		//cable->SetRestitution(0.8f);

		ParticleGravity* gravity = new ParticleGravity(mWorld);
		gravity->RegisterParticle(*mParticle1);

	}

	void ParticleContactDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		mCircle1->setPosition(centerX + mParticle1->GetPosition().x * sPixelPositionScaler, centerY - mParticle1->GetPosition().y * sPixelPositionScaler);
		mCircle2->setPosition(centerX + mParticle2->GetPosition().x * sPixelPositionScaler, centerY - mParticle2->GetPosition().y * sPixelPositionScaler);
	}

	void ParticleContactDemo::Draw()
	{
		mRenderWindow.draw(*mCircle1);
		mRenderWindow.draw(*mCircle2);
	}
}
