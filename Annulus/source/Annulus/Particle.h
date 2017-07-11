#pragma once

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class ParticleWorld;
	class Particle
	{
		friend class ParticleWorld;
	public:
		/**
		* Unregister the particle from the world.
		*/
		~Particle();
		/**
		* Get the inverse of mass of this particle.
		* @return The inverse of mass.
		*/
		std::float_t GetMassInverse() const;
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
		* Get the position of this particle.
		* @return The position of this particle.
		*/
		const glm::vec2& GetPosition() const;
		/**
		* Set the velocity of this particle.
		* @param velocity The velocity to set.
		*/
		void SetVelocity(const glm::vec2& velocity);
		/**
		* Get the velocity of this particle.
		* @return The current velocity of this particle.
		*/
		const glm::vec2& GetVelocity() const;
		/**
		* Add a force to the particle which is applied in the next iteration only.
		* @param force The force to add.
		*/
		void AddForce(const glm::vec2& force);
		/**
		* Output the data for this particle.
		*/
		void DebugParticle();
		/**
		* Get the current acceleration of the particle.
		*/
		glm::vec2 GetAcceleration() const;
	protected:
		/**
		* Updates the position and velocity of the particle based on its acceleration. (Integrator)
		* @param seconds The amount of time over which the integration is taking place. (Delta Time or dt)
		*/
		void Integrate(const std::float_t seconds);
		/**
		* The position of the particle in the world space. Defaults to origin.
		*/
		glm::vec2 mPosition;
		/**
		* The veolcity of the particle in the world space. Defaults to zero.
		*/
		glm::vec2 mVelocity;
		/**
		* The inverse of the mass of the particle.
		* Useful for both calculations, as well as representing infinite mass.
		*/
		std::float_t mMassInverse;
		/**
		* The sum total of all forces acting on a particle which is calculated each update.
		*/
		glm::vec2 mForceAccumulator;
		/**
		* Cached value of accleration acquired after estimating the force accumulator during integration.
		*/
		glm::vec2 mAcceleration;
		/**
		* The amount of damping applied to the linear motion.
		* Ranges between 0 to 1, 1 being without any damping. And 0 being the case when a particle can't move at all without an external force.
		* Damping is required to remove energy added through numerical instability in the integrator.
		*/
		std::float_t mDamping;
	private:
		/**
		* Constructor.
		* Initialzes the member with default values.
		*/
		Particle();
		/**
		* Initialize the world associated with each particle.
		* @param world The world which has to be made as the owner of all particles.
		*/
		static void Initialize(ParticleWorld& world);
		/**
		* The world with which each particle is associated.
		*/
		static ParticleWorld* sOwnerWorld;
	public:
		static const std::float_t sDefaultDamping;
		static const std::float_t sDefaultMassInverse;
	};
}