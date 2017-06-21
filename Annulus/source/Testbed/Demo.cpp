#include "pch.h"
#include "Demo.h"
#include "World.h"

#include <SFML/Graphics.hpp>

using namespace Annulus;

namespace Demos
{

	const std::float_t Demo::sPixelPositionScaler = 1.0f;
	const std::float_t Demo::sParticleRadius = 5.0f;

	Demo::Demo(sf::RenderWindow& renderWindow, Annulus::World& world) : mRenderWindow(renderWindow), mWorld(world), mView(&renderWindow.getView())
	{

	}
}
