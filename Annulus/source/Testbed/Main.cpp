// Common for both mass aggregate and rigid body Dynamics.
#include "pch.h"
#include "GameClock.h"
#include "GameTime.h"
#include "Settings.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

// Mass aggregate engine specific headers.
#include "Particle.h"
#include "ParticleWorld.h"

// Rigid body dynamics specfic headers.
#include "World.h"

// Demos
#include "ParticleSpringDemo.h"
#include "ParticleAnchoredSpringDemo.h"
#include "ParticleBungeeDemo.h"
#include "ParticleContactDemo.h"
#include "TorqueDemo.h"
#include "CircleContactDemo.h"
#include "RigidBodiesDemo.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define DEMO_COUNT 7

using namespace Annulus;
using namespace Demos;

int  main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Annulus Physics Engine Testbed");

	// Create a clock and game time objecs
	GameClock gameClock;
	GameTime gameTime;

	// Create a world with default settings
	Settings settings;
#if DEMO_COUNT <= 4
	ParticleWorld world(settings);
#elif DEMO_COUNT > 4
	World world(settings);
#endif

	// Create the demo scene
#if DEMO_COUNT == 1
	ParticleSpringDemo demo(window, world);
#elif DEMO_COUNT == 2
	ParticleAnchoredSpringDemo demo(window, world);
#elif DEMO_COUNT == 3
	ParticleBungeeDemo demo(window, world);
#elif DEMO_COUNT == 4
	ParticleContactDemo demo(window, world);
#elif DEMO_COUNT == 5
	TorqueDemo demo(window, world);
#elif DEMO_COUNT == 6
	CircleContactDemo demo(window, world);
#elif DEMO_COUNT == 7
	RigidBodiesDemo demo(window, world);
#endif

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Handle closing of the window
			if (event.type == sf::Event::Closed)
			{ 
				window.close();
			}
			// Handle resizing of screen to not affect the scaling and treat the world to be bigger than the viewport
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, static_cast<std::float_t>(event.size.width), static_cast<std::float_t>(event.size.height));
				window.setView(sf::View(visibleArea));
			}
			// If user presses R then reset the demo.
			if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Key::R)
			{
				demo.Initialize();
				std::cout << "\n\n DEMO INITIALIZED \n" << std::endl;
			}
			// Handle Input other than resetting of the demo scene in case of RigidBody demos.
#if DEMO_COUNT > 4
			demo.ProcessInput(event);
#endif
		}

		// Update Time
		gameClock.UpdateGameTime(gameTime);
		std::chrono::nanoseconds deltaNanoseconds = gameTime.ElapsedGameTime();
		
		// Physics Update
		world.Update(deltaNanoseconds);
		demo.Update(deltaNanoseconds);
		//std::cout << "Total Time: " << (gameTime.TotalGameTime().count() / 1000000000.0f) << std::endl;

		// Rendering
		window.clear(sf::Color(100, 149, 237, 1));
		demo.Draw();

		window.display();
	}
	return 0;
}