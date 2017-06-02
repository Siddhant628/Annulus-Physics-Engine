#include "pch.h"
#include <SFML/Graphics.hpp>
#include <chrono>

#include "World.h"
#include "Settings.h"
#include "GameClock.h"
#include "GameTime.h"


int  main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setPosition(90, 90);
	shape.setFillColor(sf::Color::Blue);

	// Create a clock and game time objecs
	Annulus::GameClock gameClock;
	Annulus::GameTime gameTime;
	// Create a world with default settings
	Annulus::Settings settings;
	Annulus::World world(settings);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		gameClock.UpdateGameTime(gameTime);
		
		std::chrono::milliseconds deltaMilliseconds = gameTime.ElapsedGameTime();
		world.Update(deltaMilliseconds);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
