#pragma once

namespace Annulus
{
	/**
	* The different types of colliders. Used for performing different collision detection and resolution techniques.
	*/
	enum class ColliderType
	{
		Default,
		Circle,
		Rectangle,
		Polygon
	};

	/**
	* The different layers of collisions. Can be used to sort different colliders which may collide. Colliders in same layer would interact only.
	*/
	enum class CollisionLayer
	{
		DefaultLayer,
		SecondLayer,
		ThirdLayer
	};

	class RigidBody;
	class World;
	
	/**
	* The primitive which can participate in rigid body collisions.
	*/
	class Collider
	{
		friend class World;
	public:
		/**
		* Destructor.
		* Unregister this collider from the world.
		*/
		virtual ~Collider();
		
		/**
		* Get the collider type for this collider.
		*/
		ColliderType GetColliderType();
		/**
		* Get the collision layer for this collider.
		*/
		CollisionLayer GetCollisionLayer();
		/**
		* Set the collision layer for this collider.
		* @param layer The collision layer to set.
		*/
		void SetCollisionLayer(CollisionLayer layer);
		/**
		* Deleted copy and move operations.
		*/
		Collider(const Collider&) = delete;
		Collider& operator=(const Collider&) = delete;
		Collider(Collider&&) = delete;
		Collider& operator=(Collider&&) = delete;
	protected:
		/**
		* Constructor.
		* Register this collider to the world.
		* @param body The rigid body with which this collider is associated.
		*/
		Collider(const RigidBody& body);
		
		/**
		* The rigid body with which this collider is associated. 
		*/
		const RigidBody* mRigidBody;
		/**
		* The type of collider.
		*/
		ColliderType mColliderType;
		/**
		* The collision layer for this collider.
		*/
		CollisionLayer mCollisionLayer;
	private:
		/**
		* Initialize colliders for this specific world. The colliders will register to this world.
		* @param world The world with which colliders should get associated.
		*/
		static void Initialize(World& world);
		/**
		* A pointer to the world which will own all the colliders.
		*/
		static World* mOwnerWord;
	};
}