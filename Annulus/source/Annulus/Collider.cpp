#include "pch.h"
#include "Collider.h"

namespace Annulus
{
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

	}
}
