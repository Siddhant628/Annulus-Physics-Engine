#include "pch.h"
#include "Collider.h"

#include "World.h"
#include "RigidBody.h"

namespace Annulus
{
	World* Collider::mOwnerWord = nullptr;

	Collider::~Collider()
	{
		mOwnerWord->UnregisterCollider(*this);
	}

	ColliderType Collider::GetColliderType() const
	{
		return mColliderType;
	}

	CollisionLayer Collider::GetCollisionLayer() const
	{
		return  mCollisionLayer;
	}

	void Collider::SetCollisionLayer(CollisionLayer layer)
	{
		mCollisionLayer = layer;
	}

	const glm::vec2& Collider::GetPosition() const
	{
		return mRigidBody->GetPosition();
	}

	Collider::Collider(const RigidBody& body) : mRigidBody(&body), mColliderType(ColliderType::Default), mCollisionLayer(CollisionLayer::DefaultLayer)
	{
		mOwnerWord->RegisterCollider(*this);
	}

	void Collider::Initialize(World& world)
	{
		mOwnerWord = &world;
	}
}
