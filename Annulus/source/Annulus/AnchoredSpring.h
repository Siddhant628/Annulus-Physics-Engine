#pragma once

#include "ForceGenerator.h"

#define GLM_FORCE_CXX98
#include "glm/glm.hpp"

namespace Annulus
{
	class RigidBody;

	class AnchoredSpring final : public ForceGenerator
	{
	public:
		/**
		* Constructor.
		* @param body The rigid body over which this force generator acts.
		* @param localConnection The relative position of the connection to the spring.
		*/
		AnchoredSpring(RigidBody& body, const glm::vec2& localConnection);
		/**
		* Destructor.
		*/
		virtual ~AnchoredSpring() = default;
		/**
		* Set the rest length for this spring.
		* @param length The length to set.
		*/
		void SetRestLength(std::float_t length);
		/**
		* Set the spring constant for this spring.
		* @param constant The spring constant for this spring.
		*/
		void SetSpringConstant(std::float_t constant);
		/**
		* Set the anchor point for this spring.
		* @param anchor The position to set as the anchor of the spring.
		*/
		void SetAnchor(const glm::vec2& anchor);

		/**
		* Update the force acting on a rigid body for this frame.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		virtual void UpdateForce(std::float_t seconds) override;
	private:
		/**
		* The rest length of this spring.
		*/
		std::float_t mRestLength;
		/**
		* The spring constant of this spring.
		*/
		std::float_t mSpringConstant;
		/**
		* The position of the anchor to which the other end of the spring is connected.
		*/
		glm::vec2 mAnchorPosition;
		/**
		* The point in local space at which this spring is connected to the rigid body.
		*/
		glm::vec2 mLocalConnectionPoint;
		/**
		* The body on which this spring force acts.
		*/
		RigidBody* mBody;
	};
}