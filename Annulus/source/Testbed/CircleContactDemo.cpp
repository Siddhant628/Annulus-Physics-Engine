#include "pch.h"
#include "CircleContactDemo.h"

#include "World.h"
#include "RigidBody.h"
#include "Circle.h"

using namespace Annulus;

namespace Demos
{
	const float_t CircleContactDemo::sCircleRadius = 100.0f;
	const glm::vec2 CircleContactDemo::sInitialPosition1 = glm::vec2(-200.0f, -20.0f);
	const glm::vec2 CircleContactDemo::sInitialPosition2 = glm::vec2(200.0f, 100.0f);
	const glm::vec2 CircleContactDemo::sInitialVelocity1 = glm::vec2(50.0f, 0.0f);
	const glm::vec2 CircleContactDemo::sInitialVelocity2 = glm::vec2(-50.0f, 0.0f);

	CircleContactDemo::CircleContactDemo(sf::RenderWindow& renderWindow, Annulus::World& world) : 
		Demo(renderWindow, world),
		mRigidBody1(nullptr),
		mRigidBody2(nullptr),
		mCircle1(nullptr),
		mCircle2(nullptr),
		mCircleCollider1(nullptr),
		mCircleCollider2(nullptr)
	{
		// Create the rigid bodies.
		mRigidBody1 = new RigidBody();
		mRigidBody1->SetInertia(30);

		mRigidBody1->SetAngularDamping(0.2f);
		mRigidBody1->SetLinearDamping(0.1f);

		mRigidBody2 = new RigidBody();
		mRigidBody2->SetInertia(30);

		mRigidBody2->SetAngularDamping(0.2f);
		mRigidBody2->SetLinearDamping(0.1f);

		// Create the colliders associated with rigid bodies.
		mCircleCollider1 = new Circle(*mRigidBody1, sCircleRadius);
		
		mCircleCollider2 = new Circle(*mRigidBody2, sCircleRadius + 30.0f);

		// Create the visualization circles.
		mCircle1 = new sf::CircleShape(sCircleRadius);
		mCircle1->setOrigin(sCircleRadius, sCircleRadius);

		mCircle2 = new sf::CircleShape(sCircleRadius + 30.0f);
		mCircle2->setOrigin(sCircleRadius + 30.0f, sCircleRadius + 30.0f);

		// Create the contact visulaization.
		mCircle3 = new sf::CircleShape(sPointSize);
		mCircle3->setOrigin(sPointSize, sPointSize);
		mCircle3->setFillColor(sf::Color::Cyan);

		Initialize();
	}

	CircleContactDemo::~CircleContactDemo()
	{
		delete mCircle1;
		delete mCircle2;
	}

	void CircleContactDemo::Initialize()
	{
		mRigidBody1->SetVelocity(sInitialVelocity1);
		mRigidBody1->SetPosition(sInitialPosition1);
		mRigidBody1->SetOrientation(Orientation());
		mRigidBody1->SetRotation(0);

		mRigidBody2->SetVelocity(sInitialVelocity2);
		mRigidBody2->SetPosition(sInitialPosition2);
		mRigidBody2->SetOrientation(Orientation());
		mRigidBody2->SetRotation(0);

		mCircle1->setFillColor(sf::Color::Magenta);
		mCircle2->setFillColor(sf::Color::Magenta);
	}

	void CircleContactDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		// Update the position of the rigid body.
		mCircle1->setPosition(centerX + mCircleCollider1->GetPosition().x, centerY - mCircleCollider1->GetPosition().y);
		mCircle2->setPosition(centerX + mCircleCollider2->GetPosition().x, centerY - mCircleCollider2->GetPosition().y);
		if (mWorld.GetContacts().size() == 1)
		{
			mCircle1->setFillColor(sf::Color::Blue);
			mCircle2->setFillColor(sf::Color::Blue);
		}
		else
		{
			mCircle1->setFillColor(sf::Color::Magenta);
			mCircle2->setFillColor(sf::Color::Magenta);
		}
	}

	void CircleContactDemo::Draw()
	{
		mRenderWindow.draw(*mCircle1);
		mRenderWindow.draw(*mCircle2);

		if (mWorld.GetContacts().size() == 1)
		{
			std::float_t centerX = mView->getSize().x / 2;
			std::float_t centerY = mView->getSize().y / 2;
			// Draw the point of contact.
			const Contact& contact = *mWorld.GetContacts().at(0);
			sf::Vector2f contactPoint(centerX + contact.GetPosition().x, centerY - contact.GetPosition().y);
			mCircle3->setPosition(contactPoint.x, contactPoint.y);
			mRenderWindow.draw(*mCircle3);
			// Draw the contact normal.
			const glm::vec2& normal = contact.GetNormal();
			sf::Vector2f normalEnd(centerX + normal.x * sCircleRadius * 2, centerY - normal.y * sCircleRadius * 2);

			sf::Vertex contactNormal[] =
			{
				sf::Vertex(contactPoint, sf::Color::Cyan),
				sf::Vertex(normalEnd, sf::Color::Cyan)
			};
			mRenderWindow.draw(contactNormal, 2, sf::Lines);
		}
	}
}