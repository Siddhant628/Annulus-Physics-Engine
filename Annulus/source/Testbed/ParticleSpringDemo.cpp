#include "pch.h"
#include "ParticleSpringDemo.h"

#include "Particle.h"
#include "World.h"
#include "ParticleSpring.h"

#define SPRING_REST_LENGTH 5.0f;

using namespace Annulus;

namespace Demos
{
	const std::float_t ParticleSpringDemo::sSpringRestLength = 300.0f;
	const std::float_t ParticleSpringDemo::sSpringConstant = 1.5f;
	const glm::vec2 ParticleSpringDemo::sParticlePosition1 = glm::vec2(-140.0f, 0.0f);
	const glm::vec2 ParticleSpringDemo::sParticlePosition2 = glm::vec2(140.0f, 0.0f);

	ParticleSpringDemo::ParticleSpringDemo(sf::RenderWindow& renderWindow, Annulus::World& world) : Demo(renderWindow, world), mParticle1(nullptr), mParticle2(nullptr), mSpring(nullptr), mCircle1(nullptr), mCircle2(nullptr)
	{

	}

	ParticleSpringDemo::~ParticleSpringDemo()
	{
		delete mSpring;
	}

	void ParticleSpringDemo::Initialize()
	{
		// Create particles
		mParticle1 = mWorld.CreateParticle();
		mParticle1->SetPosition(sParticlePosition1);
		mParticle1->SetDamping(0.9f);

		mParticle2 = mWorld.CreateParticle();
		mParticle2->SetPosition(sParticlePosition2);
		mParticle2->SetDamping(0.9f);

		// Create spring force generator
		mSpring = new ParticleSpring(*mParticle1, *mParticle2);
		mSpring->SetRestLength(sSpringRestLength);
		mSpring->SetSpringConstant(sSpringConstant);
		
		// Create circles to visualize particles
		mCircle1 = new sf::CircleShape(sParticleRadius);
		mCircle1->setPosition(0, 0);
		mCircle1->setFillColor(sf::Color::Red);

		mCircle2 = new sf::CircleShape(sParticleRadius);
		mCircle2->setPosition(0, 0);
		mCircle2->setFillColor(sf::Color::Red);
	}

	void ParticleSpringDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		mCircle1->setPosition(centerX + mParticle1->GetPosition().x * sPixelPositionScaler, centerY - mParticle1->GetPosition().y * sPixelPositionScaler);
		mCircle2->setPosition(centerX + mParticle2->GetPosition().x * sPixelPositionScaler, centerY - mParticle2->GetPosition().y * sPixelPositionScaler);
	}

	void ParticleSpringDemo::Draw()
	{
		mRenderWindow.draw(*mCircle1);
		mRenderWindow.draw(*mCircle2);
	}
}
