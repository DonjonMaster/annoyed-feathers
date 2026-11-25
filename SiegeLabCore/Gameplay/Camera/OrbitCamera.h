#pragma once
#include "ICameraController.h"
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class OrbitCamera : public ICameraController , public Camera3D
{
private:
  ICameraController* camera_controller_;
public:
  void Update(const InputSnapshot& input, float dt) override;
  Vector3 Position() const;
  Vector3 target = {0, 0, 0};
  float yaw = 0;
  float pitch = 0;
  float rotationSpeed = 2.0f;
  float radius = 10;
};
