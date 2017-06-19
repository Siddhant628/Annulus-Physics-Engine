#include "pch.h"
#include "GameClock.h"
#include "GameTime.h"
#include "World.h"
#include "Settings.h"

#include "Particle.h"
#include "ParticleGravity.h"
#include "ParticleSpring.h"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

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
	
	Particle* particle = world.CreateParticle();
	particle->SetVelocity(glm::vec2(0.0f, 0.0f));
	particle->SetPosition(glm::vec2(-5.0f, 0.0f));
	particle->SetDamping(0.9f);
	
	Particle* particle2 = world.CreateParticle();
	particle2->SetVelocity(glm::vec2(0.0f, 0.0f));
	particle2->SetPosition(glm::vec2(5.0f, 0.0f));
	particle2->SetDamping(0.9f);

	ParticleSpring spring(*particle, *particle2);
	spring.SetRestLength(5.0f);
	spring.SetSpringConstant(1.0f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Update game time
		gameClock.UpdateGameTime(gameTime);
		std::chrono::nanoseconds deltaNanoseconds = gameTime.ElapsedGameTime();
		
		// Perform physics update, rendering, etc.
		world.Update(deltaNanoseconds);
		//std::cout << "Total Time: " << (gameTime.TotalGameTime().count() / 1000000000.0f) << std::endl;
		std::cout << "Distance: " << glm::length(particle->GetPosition() - particle2->GetPosition()) << std::endl;

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}