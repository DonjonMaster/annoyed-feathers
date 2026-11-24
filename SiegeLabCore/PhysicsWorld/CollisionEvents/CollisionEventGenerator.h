#pragma once
#include "SiegeLabCore/PhysicsWorld/ContactSnapshot.h"

class CollisionEventGenerator
{
private:
  void Generate(ContactSnapshot snapshot);
  void Reset();
};
