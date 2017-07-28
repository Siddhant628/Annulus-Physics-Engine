#include "pch.h"
#include "RigidBodiesDemo.h"
#include "Circle.h"

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"

using namespace Annulus;

namespace Demos
{
	const std::float_t RigidBodiesDemo::sPlanetRadius = 80.0f;
	const std::float_t RigidBodiesDemo::sMinSatteliteRadius = 25.0f;
	const std::float_t RigidBodiesDemo::sMaxSatteliteRadius = 65.0f;
	const std::float_t RigidBodiesDemo::sDensityOfCircle = 1.0f;
	const std::float_t RigidBodiesDemo::sMinRotation = 10.0f;
	const std::float_t RigidBodiesDemo::sMaxRotation = 50.0f;
	const std::float_t RigidBodiesDemo::sMinSpeed = 10.0f;
	const std::float_t RigidBodiesDemo::sMaxSpeed = 50.0f;

	RigidBodiesDemo::RigidBodiesDemo(sf::RenderWindow& renderWindow, Annulus::World& world) : Demo(renderWindow, world)
	{

	}

	RigidBodiesDemo::~RigidBodiesDemo()
	{
		for(auto shape : mShapes)
		{
			delete shape;
		}
	}

	void RigidBodiesDemo::Initialize()
	{
		// Delete all the rigidbodies and the shapes used to represent them.
		for (auto shape : mShapes)
		{
			delete mBodies[shape];
			delete shape;
		}
		mBodies.clear();
		mShapes.clear();
		// Delete all the colliders in the simulation.
		for(auto collider : mColliders)
		{
			delete collider;
		}
		mColliders.clear();
	}

	void RigidBodiesDemo::Update(std::chrono::nanoseconds nanoseconds)
	{
		nanoseconds;
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;

		for(auto it = mShapes.begin(); it != mShapes.end(); ++it)
		{
			(*it)->setPosition(centerX + mBodies[(*it)]->GetPosition().x, centerY - mBodies[(*it)]->GetPosition().y);
			(*it)->setRotation(mBodies[(*it)]->GetOrientation().GetOrientationDegrees() * -1);
		}
	}

	void RigidBodiesDemo::Draw()
	{
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;
		for(auto shape : mShapes)
		{
			mRenderWindow.draw(*shape);
			
			const RigidBody& body = *mBodies[shape];
			// Get the position of the center of the circle.
			sf::Vector2f position(centerX + body.GetPosition().x, centerY - body.GetPosition().y);
			// Get the point on circle which would have been parallel to x on 0 rotation.
			std::float_t radius = reinterpret_cast<sf::CircleShape*>(shape)->getRadius();
			sf::Vector2f terminal(centerX + body.GetPosition().x + radius * body.GetOrientation().GetOrientationVector().x, centerY - body.GetPosition().y - radius * body.GetOrientation().GetOrientationVector().y);
			// Assemble and draw a line between the two points.
			sf::Vertex line[] =
			{
				sf::Vertex(position, sf::Color::White),
				sf::Vertex(terminal, sf::Color::White)
			};
			mRenderWindow.draw(line, 2, sf::Lines);
		}
	}

	void RigidBodiesDemo::ProcessInput(const sf::Event& event)
	{
		if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			SpawnCircle(sf::Mouse::getPosition(mRenderWindow));
		}
	}

	void RigidBodiesDemo::SpawnCircle(const sf::Vector2i& position)
	{
		std::float_t centerX = mView->getSize().x / 2;
		std::float_t centerY = mView->getSize().y / 2;

		// Create the circle with random radius.
		std::float_t radius = rand() % static_cast<std::int32_t>(sMaxSatteliteRadius - sMinSatteliteRadius) + sMinSatteliteRadius + 1;
		sf::CircleShape* shape = new sf::CircleShape(radius);
		shape->setOutlineColor(sf::Color::White);
		shape->setOutlineThickness(1.0f);
		shape->setFillColor(sf::Color::Black);
		shape->setOrigin(radius, radius);
		mShapes.push_back(shape);
		
		// Create a rigid body with appropriate inertia and mass. Give it a random linear and angular velocity.
		mBodies[shape] = new RigidBody(); 
		mBodies[shape]->SetMass(10);
		mBodies[shape]->SetInertia(30);
		mBodies[shape]->SetMass(radius * 1);
		mBodies[shape]->SetInertia(radius * 5);
		mBodies[shape]->SetVelocity(glm::circularRand(1.0f) * (rand() % static_cast<std::int32_t>(sMaxSpeed - sMinSpeed) + sMinSpeed + 1) );
		mBodies[shape]->SetRotation(rand() % static_cast<std::int32_t>(sMaxRotation - sMinRotation) + sMinRotation + 1);
		mBodies[shape]->SetPosition(glm::vec2(position.x - centerX, centerY - position.y));

		// Attach a collider to the rigidbody.
		mColliders.push_back(new Annulus::Circle(*mBodies[shape], radius));
	}
}
