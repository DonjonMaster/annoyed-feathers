#pragma once
#include "Cyclone/include/body.h"
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"

enum SphereOrBox
{
  kSphere,
  kBox
};

struct PhysicsRegistration
{
  EntityId entityId;
  cyclone::RigidBody* body = nullptr;
  cyclone::CollisionSphere* collision_sphere = nullptr;
  cyclone::CollisionBox* collision_box = nullptr;
  SphereOrBox kind;
};
