#pragma once
#include "Cyclone/include/body.h"
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"

enum class CollisionEventType
{
  Enter,
  Exit
};

struct CollisionEvent
{
  CollisionEventType type;
  EntityId idA;
  EntityId idB;
  cyclone::Vector3 point;
  cyclone::Vector3 normal;
  double closingSpeed = 0.0f;
};
