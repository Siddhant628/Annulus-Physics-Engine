#include "pch.h"
#include <SFML/Graphics.hpp>

#include "World.h"

int  main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setPosition(90, 90);
	shape.setFillColor(sf::Color::Blue);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
