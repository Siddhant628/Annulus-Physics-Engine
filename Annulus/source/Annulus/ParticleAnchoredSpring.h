#pragma once
#include "ParticleForceGenerator.h"

#define GLM_FORCE_CXX98
#include <glm/glm.hpp>

namespace Annulus
{
	class World;

	/**
	* A particle force generator which anchors a spring to a specific position in the space.
	*/
	class ParticleAnchoredSpring : protected ParticleForceGenerator
	{
	public:
		/**
		* Constructor.
		* @param particle A reference to the particle for which this force generator is being created.
		*/
		ParticleAnchoredSpring(Particle& particle);
		/**
		* Destructor.
		*/
		~ParticleAnchoredSpring() = default;
		/**
		* Update the force acting on a particle for this frame.
		* @param particle The particle on which the force needs to be applied.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		void UpdateForce(Particle& particle, const std::float_t& seconds) override;
		/**
		* Set the rest length for this spring force generator.
		* @param restLength The length to set.
		*/
		void SetRestLength(const std::float_t& restLength);
		/**
		* Set the spring constant for this spring force generator.
		* @param springConstant The spring constant value to set.
		*/
		void SetSpringConstant(const std::float_t& springConstant);
		/**
		* Set the anchor point for this particle force generator.
		* @param anchorPoint The position to set for the anchor point.
		*/
		void SetAnchorPoint(const glm::vec2& anchorPoint);
	private:
		/**
		* The length of the spring, i.e. the length at which no force is exerted on either of the particles.
		*/
		std::float_t mRestLength;
		/**
		* The spring constant for this spring.
		*/
		std::float_t mSpringConstant;
		/**
		* The position of the anchor point.
		*/
		glm::vec2 mAnchor;
	};
}