#pragma once
#include "Cyclone/include/body.h"
#include "Cyclone/include/collide_fine.h"

enum SphereOrBox
{
  kSphere,
  kBox
};

class PhysicsRegistration
{
private:
  int entityId;
  cyclone::RigidBody* body;
  cyclone::CollisionPrimitive* collider;
  SphereOrBox kind;
};
