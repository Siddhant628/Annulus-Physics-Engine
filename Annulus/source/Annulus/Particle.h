#pragma once

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class Particle
	{
		friend class World;
	public:
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
		/**
		* Set the position of this particle.
		* @param position The position to set.
		*/
		void SetPosition(const glm::vec2& position);
		/**
		* Set the velocity of this particle.
		* @param velocity The velocity to set.
		*/
		void SetVelocity(const glm::vec2& velocity);
		/**
		* Set the acceleration of this particle.
		* @param acceleration The acceleration to set.
		*/
		void SetAcceleration(const glm::vec2& acceleration);
		/**
		* Output the data for this particle.
		*/
		void DebugParticle();
	protected:
		/**
		* Updates the position and velocity of the particle based on its acceleration. (Integrator)
		* @param nanoseconds The amount of time over which the integration is taking place. (Delta Time - dt)
		*/
		void Integrate(std::chrono::nanoseconds nanoseconds);
		/**
		* The position of the particle in the world space. Defaults to origin.
		*/
		glm::vec2 mPosition;
		/**
		* The veolcity of the particle in the world space. Defaults to zero.
		*/
		glm::vec2 mVelocity;
		/**
		* The constant acceleration acting on the particle, like gravity, etc. Defaults to gravity.
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
	private:
		/**
		* Constructor.
		* Initialzes the member with default values.
		*/
		Particle();
	public:
		static const std::float_t sDefaultDamping;
		static const std::float_t sDefaultMassInverse;
	};
}