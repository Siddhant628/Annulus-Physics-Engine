#pragma once
#include "ParticleDemo.h"

#define GLM_FORCE_CXX98
#include <glm/glm.hpp>

namespace Annulus
{
	class Particle;
}

namespace Demos
{
	class ParticleContactDemo : public ParticleDemo
	{
	public:
		/**
		* Constructor.
		* @param renderWindow A reference to the RenderWindow for which this demo is created.
		* @param world A reference to the world for which this demo is created.
		*/
		ParticleContactDemo(sf::RenderWindow& renderWindow, Annulus::ParticleWorld& world);
		/**
		* Destructor.
		*/
		~ParticleContactDemo();
		/**
		* Initialize this demo.
		*/
		virtual void Initialize() override;
		/**
		* The Update method for this demo.
		* @param nanoseconds The amount of time over which the Update is called.
		*/
		virtual void Update(std::chrono::nanoseconds nanoseconds) override;
		/**
		* Draw the demo.
		*/
		virtual void Draw() override;
	private:
		/**
		* Particle in demo.
		*/
		Annulus::Particle* mParticle1;
		/**
		* Particle in demo.
		*/
		Annulus::Particle* mParticle2;
		/**
		* Particle in demo.
		*/
		Annulus::Particle* mParticle3;
		/**
		* Particle in demo.
		*/
		Annulus::Particle* mParticle4;


		/**
		* Circle representing a particle.
		*/
		sf::CircleShape* mCircle1;
		/**
		* Circle representing a particle.
		*/
		sf::CircleShape* mCircle2;
		/**
		* Circle representing a particle.
		*/
		sf::CircleShape* mCircle3;
		/**
		* Circle representing a particle.
		*/
		sf::CircleShape* mCircle4;
		/**
		* The initial position of the particle.
		*/
		const static glm::vec2 sParticlePosition1;
		/**
		* The initial position of the particle.
		*/
		const static glm::vec2 sParticlePosition2;
		/**
		* The initial position of the particle.
		*/
		const static glm::vec2 sParticlePosition3;
		/**
		* The initial position of the particle.
		*/
		const static glm::vec2 sParticlePosition4;
	};
}