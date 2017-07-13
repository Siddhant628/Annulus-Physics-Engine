#pragma once
#include "Demo.h"

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class RigidBody;
	class Gravity;
}

namespace Demos
{
	class TorqueDemo final: public Demo
	{
	public:
		/**
		* Constructor.
		* @param renderWindow A reference to the RenderWindow for which this demo is created.
		* @param world A reference to the world for which this demo is created.
		*/
		TorqueDemo(sf::RenderWindow& renderWindow, Annulus::World& world);
		/**
		* Destructor.
		*/
		virtual ~TorqueDemo();
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
		* A rigid body in the simulation.
		*/
		Annulus::RigidBody* mRigidBody;
		/**
		* A pointer to the gravitational force generator in the demo.
		*/
		Annulus::Gravity* mGravity;
		/**
		* The rectangle to visualize the simulation.
		*/
		sf::RectangleShape* mRectangle;
		/**
		* The center anchor point.
		*/
		sf::CircleShape* mCircle;
		/**
		* The center of mass point.
		*/
		sf::CircleShape* mCircleCOM;
		/**
		* The center connection point.
		*/
		sf::CircleShape* mCircleConnection;
		
		/**
		* The length of the rigid body rectangle.
		*/
		static const std::float_t sRectangleLength;
		/**
		* The height of the rigid body rectangle.
		*/
		static const std::float_t sRectangleHeight;
		/**
		* The relative connection point on the rigidbody.
		*/
		static const glm::vec2 sConnectionPoint;
	};
}