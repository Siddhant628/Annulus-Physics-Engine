#pragma once
#include "Demo.h"
#include <unordered_map>
#include "RigidBody.h"
#include "Collider.h"

namespace Demos
{
	/**
	* A demo of rigidbody physics I have implemented thus far for the presentation. This is not the final state of the project.
	*/
	class RigidBodiesDemo final : public Demo
	{
	public:
		/**
		* Constructor.
		* @param renderWindow A reference to the RenderWindow for which this demo is created.
		* @param world A reference to the world for which this demo is created.
		*/
		RigidBodiesDemo(sf::RenderWindow& renderWindow, Annulus::World& world);
		/**
		* Destructor.
		* Clear all the memory allocated to the shapes.
		*/
		virtual ~RigidBodiesDemo();
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
		/**
		* Process the input for this demo.
		* @param event The event to process.
		*/
		virtual void ProcessInput(const sf::Event& event) override;
	private:
		/**
		* Spawn a circle at a specific position in the simulation.
		* @param position The position of circle in local window space.
		*/
		void SpawnCircle(const sf::Vector2i& position);

		/**
		* A hashmap which maps each shape drawn in the demo to a rigidbody.
		*/
		std::unordered_map<sf::Shape*, Annulus::RigidBody*> mBodies;
		/**
		* The shapes which are present in the demo.
		*/
		std::vector<sf::Shape*> mShapes;
		/**
		* The colliders which are present in the demo.
		*/
		std::vector<Annulus::Collider*> mColliders;

		static const std::float_t sPlanetRadius;
		static const std::float_t sMinSatteliteRadius;
		static const std::float_t sMaxSatteliteRadius;
		static const std::float_t sDensityOfCircle;
		static const std::float_t sMinRotation;
		static const std::float_t sMaxRotation;
		static const std::float_t sMinSpeed;
		static const std::float_t sMaxSpeed;
	};
}
