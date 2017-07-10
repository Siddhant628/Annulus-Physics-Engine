#include "pch.h"
#include "ParticleDemo.h"
#include "ParticleWorld.h"

#include <SFML/Graphics.hpp>

using namespace Annulus;

namespace Demos
{

	const std::float_t ParticleDemo::sPixelPositionScaler = 1.0f;
	const std::float_t ParticleDemo::sParticleRadius = 5.0f;

	ParticleDemo::ParticleDemo(sf::RenderWindow& renderWindow, Annulus::ParticleWorld& world) : mRenderWindow(renderWindow), mWorld(world), mView(&renderWindow.getView())
	{

	}
}
