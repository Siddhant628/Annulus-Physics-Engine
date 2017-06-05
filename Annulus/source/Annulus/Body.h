#pragma once

#define GLM_FORCE_CXX98
#include <glm/glm.hpp>

namespace Annulus
{
	class Shape;

	/**
	* A rigid body which can be created through a world. 
	*/
	class Body
	{
	public:
		~Body() = default;
	protected:
		/**
		* Constructor. Protected so body can only be created through a world using CreateBody method.
		*/
		Body();
		/**
		* The shape of this rigidbody.
		*/
		Shape* mShape;
		
		// Transform related data.
		/**
		* The position of this rigidbody.
		*/
		glm::vec2 mPosition;
		/**
		* The rotation of this rigidbody.
		*/
		std::float_t mRotation;
		/**
		* The velocity of this rigidbody.
		*/
		glm::vec2 mVelocity;
		/**
		* The angular velocity of this rigidbody.
		*/
		std::float_t mAngularVelocity;

		// Acceleration related data.
		/**
		* The force acting on this rigidbody.
		*/
		glm::vec2 mForce;
		/**
		* The torque acting on this rigidbody.
		*/
		std::float_t mTorque;
		
		// Mass related data.
		/**
		* The mass of this rigidbody.
		*/
		std::float_t mMass;
		/**
		* The inverse of mass of this rigidbody.
		*/
		std::float_t mMassInverse;
		/**
		* The moment of intertia of this rigidbody.
		*/
		std::float_t mMomentOfInertia;
		/**
		* The inverse of moment of intertia of this rigidbody.
		*/
		std::float_t mMomentOfIntertiaInverse;

		// TODO Add static friction, dynamic friction, restitution
	};
}