#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>

namespace Annulus 
{
	class ParticleWorld;
}

namespace Demos
{
	class Demo
	{
	public:
		/**
		* Destructor.
		*/
		virtual ~Demo() = default;
		/**
		* Initialize this demo.
		*/
		virtual void Initialize() = 0;
		/**
		* The Update method for this demo.
		* @param nanoseconds The amount of time over which the Update is called.
		*/
		virtual void Update(std::chrono::nanoseconds nanoseconds) = 0;
		/**
		* Draw the demo.
		*/
		virtual void Draw() = 0;
	protected:
		/**
		* Constructor.
		* @param renderWindow A reference to the RenderWindow for which this demo is created.
		* @param world A reference to the world for which this demo is created.
		*/
		Demo(sf::RenderWindow& renderWindow, Annulus::ParticleWorld& world);
		/**
		* A reference to the RenderWindow for which this demo is created.
		*/
		sf::RenderWindow& mRenderWindow;
		/**
		* A reference to the world for which this demo is created.
		*/
		Annulus::ParticleWorld& mWorld;
		/**
		* The view associated with the rendered window.
		*/
		const sf::View* mView;
		/**
		* The magnitude with each position is scaled to get the pixel position for rendering on the display.
		*/
		const static std::float_t sPixelPositionScaler;
		/**
		* The radius of the circles representing each particle.
		*/
		const static std::float_t sParticleRadius;
	};
}