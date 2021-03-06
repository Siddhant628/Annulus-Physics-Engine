#include "pch.h"
#include "ParticleBungeeDemo.h"

#include "ParticleWorld.h"
#include "Particle.h"

using namespace Annulus;

namespace Demos
{
	const std::float_t ParticleBungeeDemo::sSpringRestLength = 100.0f;
	const std::float_t ParticleBungeeDemo::sSpringConstant = 1.5f;
	const glm::vec2 ParticleBungeeDemo::sParticlePosition1 = glm::vec2(-50.0f, 50.0f);
	const glm::vec2 ParticleBungeeDemo::sParticlePosition2 = glm::vec2(0.0f, 0.0f);

	ParticleBungeeDemo::ParticleBungeeDemo(sf::RenderWindow& renderWindow, Annulus::ParticleWorld& world) : ParticleDemo(renderWindow, world), mParticle1(nullptr), mParticle2(nullptr), mCircle1(nullptr), mCircle2(nullptr), mBungee(nullptr)
	{
		mParticle1 = mWorld.CreateParticle();
		mParticle2 = mWorld.CreateParticle();

		mBungee = new ParticleBungee(*mParticle1, *mParticle2);

		// Create gravitational force generator
		mGravity = new ParticleGravity(mWorld);
		mGravity->RegisterParticle(*mParticle1);

		mCircle1 = new sf::CircleShape(sParticleRadius);
		mCircle2 = new sf::CircleShape(sParticleRadius);

		Initialize();
	}

	ParticleBungeeDemo::~ParticleBungeeDemo()
	{
		delete mBungee;
		delete mGravity;
	}

	void ParticleBungeeDemo::Initialize()
	{
		// Initialize particles
		mParticle1->SetPosition(sParticlePosition1);
		mParticle1->SetDamping(0.9f);
		mParticle1->SetVelocity(glm::vec2(0, 0));

		mParticle2->SetPosition(sParticlePosition2);
		mParticle2->SetDamping(0.9f);
		mParticle2->SetVelocity(glm::vec2(0, 0));

		// Initialize spring force generator
		mBungee->SetRestLength(sSpringRestLength);
		mBungee->SetSpringConstant(sSpringConstant);

		// Initialize circles to visualize particles
		mCircle1->setPosition(0, 0);
		mCircle1->setFillColor(sf::Color::Red);

		mCircle2->setPosition(0, 0);
		mCircle2->setFillColor(sf::Color::Black);
	}

	void ParticleBungeeDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;

		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		mCircle1->setPosition(centerX + mParticle1->GetPosition().x * sPixelPositionScaler, centerY - mParticle1->GetPosition().y * sPixelPositionScaler);
		mCircle2->setPosition(centerX + mParticle2->GetPosition().x * sPixelPositionScaler, centerY - mParticle2->GetPosition().y * sPixelPositionScaler);
	}

	void ParticleBungeeDemo::Draw()
	{
		mRenderWindow.draw(*mCircle1);
		mRenderWindow.draw(*mCircle2);
	}
}
