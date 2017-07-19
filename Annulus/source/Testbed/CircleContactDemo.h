#pragma once
#include "Demo.h"

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class RigidBody;
	class Collider;
	class Circle;
}

namespace Demos
{
	class CircleContactDemo final : public Demo
	{
	public:
		/**
		* Constructor.
		* @param renderWindow A reference to the RenderWindow for which this demo is created.
		* @param world A reference to the world for which this demo is created.
		*/
		CircleContactDemo(sf::RenderWindow& renderWindow, Annulus::World& world);
		/**
		* Destructor.
		*/
		virtual ~CircleContactDemo();
		/**
		* Initialize this demo.
		*/
		virtual void Initialize() override;
		/**
		* The Update method for this demo.
		* @param nanoseconds The amount of time over which the Update is called.
		*/
		virtual void Update(std::chrono::nanoseconds nanoseconds) override;
		/**
		* Draw the demo.
		*/
		virtual void Draw() override;
	private:
		/**
		* A rigid body in the demo.
		*/
		Annulus::RigidBody* mRigidBody1;
		/**
		* A rigid body in the demo.
		*/
		Annulus::RigidBody* mRigidBody2;
		/**
		* The circle collider associated with rigid body 1.
		*/
		Annulus::Circle* mCircleCollider1;
		/**
		* The circle collider associated with rigid body 1.
		*/
		Annulus::Circle* mCircleCollider2;
		/**
		* The circle which represents the collider.
		*/
		sf::CircleShape* mCircle1;
		/**
		* The circle which represents the collider.
		*/
		sf::CircleShape* mCircle2;
		/**
		* The initial position of rigid body.
		*/
		static const glm::vec2 sInitialPosition1;
		/**
		* The initial position of rigid body.
		*/
		static const glm::vec2 sInitialPosition2;
		/**
		* The initial velocity of rigid body.
		*/
		static const glm::vec2 sInitialVelocity1;
		/**
		* The initial velocity of rigid body.
		*/
		static const glm::vec2 sInitialVelocity2;
		/**
		* The radius of the circle.
		*/
		static const std::float_t sCircleRadius;
	};
}