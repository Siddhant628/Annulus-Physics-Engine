#include "pch.h"
#include <SFML/Graphics.hpp>
#include <chrono>

#include "GameClock.h"
#include "GameTime.h"
#include "World.h"
#include "Settings.h"

#include "Particle.h"

using namespace Annulus;

int  main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setPosition(90, 90);
	shape.setFillColor(sf::Color::Blue);

	// Create a clock and game time objecs
	GameClock gameClock;
	GameTime gameTime;
	// Create a world with default settings
	Settings settings;
	World world(settings);

	Particle particle;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		gameClock.UpdateGameTime(gameTime);
		std::chrono::nanoseconds deltaNanoseconds = gameTime.ElapsedGameTime();
		
		world.Update(deltaNanoseconds);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
