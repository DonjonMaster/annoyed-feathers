#pragma once
#include "Cyclone/include/body.h"

class ContactSnapshot
{
public:
  cyclone::RigidBody entityA;
  cyclone::RigidBody entityB;
  cyclone::Vector3 point;
  // normal
  double closingSpeed;
};
