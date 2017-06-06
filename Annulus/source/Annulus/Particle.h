#pragma once

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class Particle
	{
	public:
		// TODO Make the constructor private after testing
		/**
		* Constructor.
		* Initialzes the member with default values.
		*/
		Particle();
		/**
		* Destructor.
		*/
		~Particle() = default;
		/**
		* Get the inverse of mass of this particle.
		* @return The inverse of mass.
		*/
		const std::float_t& GetMassInverse() const;
		/**
		* Set the inverse of mass of this particle.
		* @param inverseMass The inverse of mass to set for this particle.
		*/
		void SetInverseMass(std::float_t inverseMass);
		/**
		* Set the mass of this particle.
		* @param mass The mass which has to be set for this particle.
		*/
		void SetMass(std::float_t mass);
		/**
		* Set the damping factor for this particle.
		* @param damping The damping factor which has to be set for this particle.
		*/
		void SetDamping(std::float_t damping);
	protected:
		/**
		* The position of the particle in the world space.
		*/
		glm::vec2 mPosition;
		/**
		* The veolcity of the particle in the world space.
		*/
		glm::vec2 mVelocity;
		/**
		* The constant acceleration acting on the particle, like gravity, etc.
		* It is assumed that the force acting on the particle is constant.
		*/
		glm::vec2 mAcceleration;
		/**
		* The amount of damping applied to the linear motion.
		* Ranges between 0 to 1, 1 being without any damping. And 0 being the case when a particle can't move at all without an external force.
		* Damping is required to remove energy added through numerical instability in the integrator.
		*/
		std::float_t mDamping;
		/**
		* The inverse of the mass of the particle.
		* Useful for both calculations, as well as representing infinite mass.
		*/
		std::float_t mMassInverse;
	public:
		static const std::float_t sDefaultDamping;
		static const std::float_t sDefaultMassInverse;
	};
}