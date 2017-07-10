#pragma once
#include "ParticleDemo.h"

#define GLM_FORCE_CXX98
#include <glm/glm.hpp>

namespace Annulus
{
	class Particle;
	class ParticleSpring;
}

namespace Demos
{
	class ParticleSpringDemo : public ParticleDemo
	{
	public:
		/**
		* Constructor.
		* @param renderWindow A reference to the RenderWindow for which this demo is created.
		* @param world A reference to the world for which this demo is created.
		*/
		ParticleSpringDemo(sf::RenderWindow& renderWindow, Annulus::ParticleWorld& world);
		/**
		* Destructor.
		*/
		~ParticleSpringDemo();
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
		* The spring force generator between the two particles.
		*/
		Annulus::ParticleSpring* mSpring;
		/**
		* Circle representing a particle.
		*/
		sf::CircleShape* mCircle1;
		/**
		* Circle representing a particle.
		*/
		sf::CircleShape* mCircle2;
		/**
		* The length of the spring in the rest state.
		*/
		const static std::float_t sSpringRestLength;
		/**
		* The spring constant for the spring.
		*/
		const static std::float_t sSpringConstant;
		/**
		* The initial position of the particle.
		*/
		const static glm::vec2 sParticlePosition1;
		/**
		* The initial position of the particle.
		*/
		const static glm::vec2 sParticlePosition2;
	};
}