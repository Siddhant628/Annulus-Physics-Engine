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

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define DEMO_COUNT 5

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
	ParticleSpringDemo springDemo(window, world);
	springDemo.Initialize();
#elif DEMO_COUNT == 2
	ParticleAnchoredSpringDemo anchoredSpringDemo(window, world);
	anchoredSpringDemo.Initialize();
#elif DEMO_COUNT == 3
	ParticleBungeeDemo bungeeDemo(window, world);
	bungeeDemo.Initialize();
#elif DEMO_COUNT == 4
	ParticleContactDemo contactDemo(window, world);
	contactDemo.Initialize();
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
		}
		// Update game time
		gameClock.UpdateGameTime(gameTime);
		std::chrono::nanoseconds deltaNanoseconds = gameTime.ElapsedGameTime();
		
		// Perform physics update, rendering, etc.
		world.Update(deltaNanoseconds);
		//std::cout << "Total Time: " << (gameTime.TotalGameTime().count() / 1000000000.0f) << std::endl;
		
		// Update the demo scene
#if DEMO_COUNT == 1
		springDemo.Update(deltaNanoseconds);
#elif DEMO_COUNT == 2
		anchoredSpringDemo.Update(deltaNanoseconds);
#elif DEMO_COUNT == 3
		bungeeDemo.Update(deltaNanoseconds);
#elif DEMO_COUNT == 4
		contactDemo.Update(deltaNanoseconds);
#endif
		// Rendering
		window.clear(sf::Color(100, 149, 237, 1));
		
		// Draw the demo scene
#if DEMO_COUNT == 1
		springDemo.Draw();
#elif DEMO_COUNT == 2
		anchoredSpringDemo.Draw();
#elif DEMO_COUNT == 3
		bungeeDemo.Draw();
#elif DEMO_COUNT == 4
		contactDemo.Draw();
#endif

		window.display();
	}
	return 0;
}