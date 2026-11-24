#pragma once
#include "OrbitCamera.h"
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class ICameraController
{
public:
  void Update(const InputSnapshot& input, float dt); 
  OrbitCamera getCamera()
  {
    return camera_;
  }
  void reset();
private:
  OrbitCamera camera_;
};
