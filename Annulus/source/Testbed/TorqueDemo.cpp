#include "pch.h"
#include "TorqueDemo.h"

#include "AnchoredSpring.h"
#include "RigidBody.h"
#include "Gravity.h"

using namespace Annulus;
using namespace sf;

namespace Demos
{
	const std::float_t TorqueDemo::sRectangleLength = 40.0f;
	const std::float_t TorqueDemo::sRectangleHeight = 40.0f;
	const glm::vec2 TorqueDemo::sConnectionPoint = glm::vec2(-20, 20);

	TorqueDemo::TorqueDemo(sf::RenderWindow& renderWindow, Annulus::World& world) :
		Demo(renderWindow, world),
		mRigidBody(nullptr),
		mGravity(nullptr),
		mRectangle(nullptr),
		mCircle(nullptr),
		mCircleCOM(nullptr),
		mCircleConnection(nullptr)
	{
		// Create the rigidbody.
		mRigidBody = new RigidBody();
		mRigidBody->SetInertia(30);

		// Create the force generator.
		mGravity = new Gravity(*mRigidBody);
		
		// Create the anchored spring.
		AnchoredSpring* anchoredSpring = new AnchoredSpring(*mRigidBody, sConnectionPoint);
		anchoredSpring->SetRestLength(150);

		// Create the anchor point, center of mass and the connection point.
		mCircle = new sf::CircleShape(sPointSize);
		mCircle->setOrigin(sPointSize / 2, sPointSize / 2);
		mCircle->setFillColor(sf::Color::Black);

		mCircleCOM = new sf::CircleShape(sPointSize);
		mCircleCOM->setOrigin(sPointSize / 2, sPointSize / 2);
		mCircleCOM->setFillColor(sf::Color::Red);

		mCircleConnection = new sf::CircleShape(sPointSize);
		mCircleConnection->setOrigin(sPointSize / 2, sPointSize / 2);
		mCircleConnection->setFillColor(sf::Color::Red);

		// Create rectangle to visualize rigid body.
		mRectangle = new sf::RectangleShape(sf::Vector2f(sRectangleLength, sRectangleHeight));
		mRectangle->setOrigin(sRectangleLength / 2, sRectangleHeight / 2);
		mRectangle->setFillColor(sf::Color::Yellow);

		Initialize();
	}

	TorqueDemo::~TorqueDemo()
	{
		delete mRectangle;
		delete mCircle;
		delete mCircleCOM;
		delete mCircleConnection;
	}

	void TorqueDemo::Initialize()
	{
		mRigidBody->SetAngularDamping(0.2f);
		mRigidBody->SetLinearDamping(0.1f);
		mRigidBody->SetVelocity(glm::vec2(0, 0));
		mRigidBody->SetPosition(glm::vec2(0, 0));
		mRigidBody->SetOrientation(Orientation());
		mRigidBody->SetRotation(0);
	}

	void TorqueDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		// Update the position of the rigid body and its rotation.
		mRectangle->setPosition(centerX + mRigidBody->GetPosition().x, centerY - mRigidBody->GetPosition().y);
		mRectangle->setRotation(mRigidBody->GetOrientation().GetOrientationDegrees() * -1);
		// Update the positions of the anchor point and the center of mass.
		mCircle->setPosition(centerX, centerY);
		mCircleCOM->setPosition(centerX + mRigidBody->GetPosition().x, centerY - mRigidBody->GetPosition().y);
		// Update the position of the connection point.
		glm::vec2 position;
		mRigidBody->GetPointInWorldSpace(sConnectionPoint, position);
		mCircleConnection->setPosition(centerX + position.x, centerY - position.y);
	}

	void TorqueDemo::Draw()
	{
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;

		mRenderWindow.draw(*mRectangle);

		mRenderWindow.draw(*mCircle);
		mRenderWindow.draw(*mCircleCOM);
		mRenderWindow.draw(*mCircleConnection);

		// Draw the lines.
		glm::vec2 position;
		mRigidBody->GetPointInWorldSpace(sConnectionPoint, position);
		sf::Vertex connectionLine[] =
		{
			sf::Vertex(sf::Vector2f(centerX + position.x, centerY - position.y), Color::Black),
			sf::Vertex(sf::Vector2f(centerX + mRigidBody->GetPosition().x, centerY - mRigidBody->GetPosition().y), Color::Black)
		};
		mRenderWindow.draw(connectionLine, 2, sf::Lines);

		sf::Vertex springLine[] =
		{
			sf::Vertex(sf::Vector2f(centerX + position.x, centerY - position.y), Color::Black),
			sf::Vertex(sf::Vector2f(centerX, centerY), Color::Black)
		};
		mRenderWindow.draw(springLine, 2, sf::Lines);
	}
}