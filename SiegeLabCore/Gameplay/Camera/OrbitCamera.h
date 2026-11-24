#pragma once
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class OrbitCamera
{
public:
  float rotationSpeed;
  Vector3 target;
  float yaw;
  float pitch;
  float radius;
  float zoom;
};
