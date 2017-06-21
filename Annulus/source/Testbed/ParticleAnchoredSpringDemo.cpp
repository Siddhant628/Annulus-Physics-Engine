#include "pch.h"
#include "ParticleAnchoredSpringDemo.h"

#include "World.h"
#include "Particle.h"

using namespace Annulus;

namespace Demos
{
	const std::float_t ParticleAnchoredSpringDemo::sSpringRestLength = 100.0f;
	const std::float_t ParticleAnchoredSpringDemo::sSpringConstant = 1.5f;
	const glm::vec2 ParticleAnchoredSpringDemo::sParticlePosition1 = glm::vec2(-100.0f, -100.0f);
	const glm::vec2 ParticleAnchoredSpringDemo::sParticlePosition2 = glm::vec2(0.0f, 0.0f);

	ParticleAnchoredSpringDemo::ParticleAnchoredSpringDemo(sf::RenderWindow& renderWindow, Annulus::World& world) : Demo(renderWindow, world), mParticle1(nullptr), mParticle2(nullptr), mCircle1(nullptr), mCircle2(nullptr), mSpring(nullptr)
	{

	}

	ParticleAnchoredSpringDemo::~ParticleAnchoredSpringDemo()
	{
		delete mSpring;
	}

	void ParticleAnchoredSpringDemo::Initialize()
	{
		// Create particles
		mParticle1 = mWorld.CreateParticle();
		mParticle1->SetPosition(sParticlePosition1);
		mParticle1->SetDamping(0.9f);

		mParticle2 = mWorld.CreateParticle();
		mParticle2->SetPosition(sParticlePosition2);
		mParticle2->SetDamping(0.9f);

		// Create spring force generator
		mSpring = new ParticleAnchoredSpring(*mParticle1);
		mSpring->SetRestLength(sSpringRestLength);
		mSpring->SetSpringConstant(sSpringConstant);
		mSpring->SetAnchorPoint(mParticle2->GetPosition());


		// Create circles to visualize particles
		mCircle1 = new sf::CircleShape(sParticleRadius);
		mCircle1->setPosition(0, 0);
		mCircle1->setFillColor(sf::Color::Red);

		mCircle2 = new sf::CircleShape(sParticleRadius);
		mCircle2->setPosition(0, 0);
		mCircle2->setFillColor(sf::Color::Black);
	}

	void ParticleAnchoredSpringDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		mSpring->SetAnchorPoint(mParticle2->GetPosition());

		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		mCircle1->setPosition(centerX + mParticle1->GetPosition().x * sPixelPositionScaler, centerY - mParticle1->GetPosition().y * sPixelPositionScaler);
		mCircle2->setPosition(centerX + mParticle2->GetPosition().x * sPixelPositionScaler, centerY - mParticle2->GetPosition().y * sPixelPositionScaler);
	}

	void ParticleAnchoredSpringDemo::Draw()
	{
		mRenderWindow.draw(*mCircle1);
		mRenderWindow.draw(*mCircle2);
	}
}
