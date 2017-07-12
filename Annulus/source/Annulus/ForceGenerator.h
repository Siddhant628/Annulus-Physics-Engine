#pragma once

namespace Annulus
{
	class World;

	/**
	* A force generator can add forces to the various rigidbodies in a simulation.
	* The world iterates over all the contained force generators and calls their UpdateForce method each iteration of the world update.
	*/
	class ForceGenerator
	{
	public:
		/**
		* Destructor.
		* Unregisters this force generator from the associated world.
		*/
		virtual ~ForceGenerator();
		/**
		* Update the force acting on a rigid body for this frame.
		* @param seconds The duration of the frame over which the force is updated.
		*/
		virtual void UpdateForce(std::float_t seconds) = 0;
	private:
		/**
		* Constructor.
		* Registers this force generator to the associated world.
		*/
		ForceGenerator();

		/**
		* Initialize the static members of this class. Called in the constructor of the world.
		* @param world The world that contains this rigid body.
		*/
		static void Initialize(World& world);
		/**
		* The world with which all the force generators are associated.
		*/
		static World* sOwnerWorld;
	};
}