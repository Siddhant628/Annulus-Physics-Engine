#pragma once
#include "Demo.h"

namespace Demos
{
	class TorqueDemo : public Demo
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
		sf::RectangleShape* mRectangle;
	};
}