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
	protected:
		/**
		*
		*/
		glm::vec2 mPosition;
		/**
		*
		*/
		Orientation mOrientation;
		/**
		*
		*/
		std::float_t mMassInverse;
		/**
		*
		*/
		glm::vec2 mVelocity;
		/**
		*
		*/
		std::float_t mRotation;
	private:
		/**
		* Initialize the static members of this class. Called in the constructor of the world
		* @param world The world that contains this rigid body.
		*/
		static void Initialize(World& world);
		/**
		* A pointer to the world which owns all the rigid bodies.
		*/
		static World* mOwnerWorld;
	};
}