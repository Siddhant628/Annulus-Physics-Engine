#pragma once

#include "ForceGenerator.h"

namespace Annulus
{
	class RigidBody;

	/**
	* A force generator which applies gravitational force to a rigid body.
	*/
	class Gravity final: public ForceGenerator
	{
	public:
		/**
		* Constructor.
		* @param body The rigid body over which the gravity acts.
		*/
		Gravity(RigidBody& body);
		/**
		* Destructor.
		*/
		virtual ~Gravity() = default;
		/**
		* Update the force acting on a rigid body for this frame.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		virtual void UpdateForce(std::float_t seconds) override;
	private:
		RigidBody* mBody;
	};
}