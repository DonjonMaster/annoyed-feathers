#pragma once
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"

class PhysicsWorld
{
public:
  void RegisterSphere(EntityId id, cyclone::RigidBody& body,
                      cyclone::CollisionSphere& sphere);
  void RegisterBox(EntityId id, cyclone::RigidBody& body,
                   cyclone::CollisionBox& box);
  void RegisterPlane(cyclone::CollisionPlane plane);
  void UnregisterObject(EntityId id);
  void Step(const float dt);
  void Reset();
};
