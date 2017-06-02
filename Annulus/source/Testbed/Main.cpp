#include "pch.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

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
	
	std::chrono::high_resolution_clock::time_point timeAtStartOfFrame;
	std::chrono::milliseconds iterationTime;

	while (window.isOpen())
	{
		timeAtStartOfFrame = gameClock.CurrentTime();
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

		iterationTime = std::chrono::duration_cast<std::chrono::milliseconds>(gameClock.CurrentTime() - timeAtStartOfFrame);		
		if(iterationTime < std::chrono::milliseconds(15))
		{
				Sleep(static_cast<DWORD>( 15 - iterationTime.count()));
		}

		window.display();
	}

	return 0;
}
