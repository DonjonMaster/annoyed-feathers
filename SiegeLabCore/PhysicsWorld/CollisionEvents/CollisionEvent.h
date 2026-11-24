#pragma once
#include "Cyclone/include/body.h"

class CollisionEvent
{
public:
  bool EnterOrExit;
  cyclone::RigidBody entityA;
  cyclone::RigidBody entityB;
  double impactSpeed;
};
