#include "pch.h"
#include "Collider.h"

#include "World.h"

namespace Annulus
{
	World* Collider::mOwnerWord = nullptr;

	Collider::~Collider()
	{
		mOwnerWord->UnregisterCollider(*this);
	}

	ColliderType Collider::GetColliderType()
	{
		return mColliderType;
	}

	CollisionLayer Collider::GetCollisionLayer()
	{
		return  mCollisionLayer;
	}

	void Collider::SetCollisionLayer(CollisionLayer layer)
	{
		mCollisionLayer = layer;
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
