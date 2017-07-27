#pragma once
#include "Demo.h"

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
		*
		*/
		~RigidBodiesDemo() = default;
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

	};
}
