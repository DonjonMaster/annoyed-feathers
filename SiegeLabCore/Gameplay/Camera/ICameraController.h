#pragma once
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class OrbitCamera;

class ICameraController
{
public:
  virtual ~ICameraController() = default;
  virtual void Update(const InputSnapshot& _input, float _dt) {}
  OrbitCamera GetCamera();
  void Reset();

private:
  OrbitCamera* m_camera = nullptr;
};
