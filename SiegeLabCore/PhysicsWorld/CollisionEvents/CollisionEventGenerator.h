#pragma once
#include "SiegeLabCore/PhysicsWorld/ContactSnapshot.h"

class CollisionEventGenerator
{
  void Generate(ContactSnapshot snapshot);
  void Reset();
};
