#pragma once
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class OrbitCamera;

class ICameraController
{
public:
  virtual ~ICameraController() = default;

  virtual void Update(const InputSnapshot& input, float dt)
  {
  }

  OrbitCamera GetCamera();
  void Reset();

private:
  OrbitCamera* camera_;
};
