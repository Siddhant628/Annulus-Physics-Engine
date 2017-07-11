#pragma once
#include "Orientation.h"

namespace Annulus
{
	/**
	* A RigidBody is the basic physical object which follows rigid body dynamics under the influence of various forces in the containing world.
	*/
	class RigidBody
	{
		friend class World;
	public:
		// Constructor and destructor.
		/**
		* Constructor.
		* Registers the rigidbody to the owner world.
		*/
		RigidBody();
		/**
		* Destructor.
		* Unregisters the rigidbody from the owner world.
		*/
		virtual ~RigidBody();
		// Getters and Setters.
		/**
		* Get the position of this rigid body.
		*/
		const glm::vec2& GetPosition() const;
		/**
		* Set the position of this rigid body.
		* @param position The position to set.
		*/
		void SetPosition(const glm::vec2& position);
		/**
		* Get the orientation of this rigid body.
		*/
		const Orientation& GetOrientation() const;
		/**
		* Set the orientation of this rigid body.
		* @param orientation The orientation to set for this body.
		*/
		void SetOrientation(const Orientation& orientation);
		/**
		* Get the velocity of this rigid body.
		*/
		const glm::vec2& GetVelocity() const;
		/**
		* Set the velocity of this rigid body.
		* @param velocity The velocity to set for this rigid body.
		*/
		void SetVelocity(const glm::vec2& velocity);
		/**
		* Get the rotation / angular velocity of this rigid body.
		*/
		std::float_t GetRotation() const;
		/**
		* Set the rotation / angular velocity of this rigid body.
		* @param rotation The rotation / angular velocity to set.
		*/
		void SetRotation(std::float_t rotation);
		/**
		* Get the inverse of mass of this rigid body.
		*/
		std::float_t GetMassInverse() const;
		/**
		* Set the inverse of mass of this rigid body.
		* @param massInverse The inverse of mass to set.
		*/
		void SetMassInverse(std::float_t massInverse);
		/**
		* Set the mass of this rigid body.
		* @param mass The mass to set for this rigid body.
		*/
		void SetMass(std::float_t mass);
		/**
		* Get the inverse of inertia for this rigid body.
		*/
		std::float_t GetInertiaInverse() const;
		/**
		* Set the inverse of inertia for this rigid body.
		* @param inertiaInverse The inverse of inertia to set for this rigid body.
		*/
		void SetInertiaInverse(std::float_t inertiaInverse);
		/**
		* Set the inertia of this rigid body.
		* @param inertia The inertia to set for this rigid body.
		*/
		void SetInertia(std::float_t inertia);
		/**
		* Get the linear damping for this rigidbody.
		*/
		std::float_t GetLinearDamping() const;
		/**
		* Set the linear damping for this rigidbody.
		* @param damping The damping factor to set [0,1].
		*/
		void SetLinearDamping(std::float_t damping);
		/**
		* Get the angular damping
		*/
		std::float_t GetAngularDamping() const;
		/**
		* Set the angular damping for this rigidbody.
		* @param damping The damping factor to set [0,1].
		*/
		void SetAngularDamping(std::float_t damping);

		// Simulation associated.
		/**
		* Add a force to the body at its center of mass, which is applied in the next iteration only.
		* @param force The force to add.
		*/
		void AddForce(const glm::vec2& force);
		/**
		* Add a force to the rigid body at a specific point.
		* Since this force is acting on a point of the object, which can be other than the conet of mass, this may generate torque.
		* @param force The force which is to be added to the rigid body.
		* @param point The point at which the force is being added.
		*/
		void AddForce(const glm::vec2& force, const glm::vec2& point);
	protected:
		/**
		* Updates the position and velocity of the particle based on the calculated acceleration. (Integrator)
		* @param seconds The amount of time over which the integration is taking place. (Delta Time or dt)
		*/
		void Integrate(std::float_t seconds);

		// State.
		/**
		* The position of this rigid body. By architecture, this is also the center of mass of the body.
		*/
		glm::vec2 mPosition;
		/**
		* The angular orientation of this rigid body.
		*/
		Orientation mOrientation;
		/**
		* The linear velocity of this rigid body.
		*/
		glm::vec2 mVelocity;
		/**
		* The angular velocity of this rigid body.
		*/
		std::float_t mRotation;
		/**
		* The inverse of mass of this rigid body. Stored as inverse to represent the case of infinite resistance and mathematical optimization.
		*/
		std::float_t mMassInverse;
		/**
		* The inverse of inertia of this rigid body. Stored as inverse to represent the case of infinite resistance and mathematical optimization.
		*/
		std::float_t mInertiaInverse;
		/**
		* The proportion of linear velocity that would sucessfully transfer to next update [0,1].
		*/
		std::float_t mLinearDamping;
		/**
		* The proportion of angular velocity that would sucessfully transfer to next update [0,1].
		*/
		std::float_t mAngularDamping;

		// Simulation associated.
		/**
		* The sum total of all forces acting on the rigid body, it is calculated each update.
		*/
		glm::vec2 mForceAccumulator;
		/**
		* The sum total of all the torque acting on this rigid body, it is calculated each update.
		*/
		std::float_t mTorqueAccumulator;
	private:
		// Initialization associated.
		/**
		* Initialize the static members of this class. Called in the constructor of the world
		* @param world The world that contains this rigid body.
		*/
		static void Initialize(World& world);
		
		// Debugging associated.
		/**
		* Output the state of rigid body.
		*/
		void DebugRigidBody();

		// Simulation associated.
		/**
		* The cached acceleration which was estimated by the integrator in this update call.
		*/
		glm::vec2 mCachedAcceleration;
		/**
		* The cached angular acceleration which was estimated by the integrator in this update call.
		*/
		std::float_t mCachedAngularAcceleration;

		// Initialization associated.
		/**
		* A pointer to the world which owns all the rigid bodies.
		*/
		static World* mOwnerWorld;
	};
}