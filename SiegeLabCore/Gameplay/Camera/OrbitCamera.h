#pragma once
#include "ICameraController.h"
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class OrbitCamera : public ICameraController, public Camera3D
{
public:
  void Update(const InputSnapshot& _input, float _dt) override;
  Vector3 GetPosition() const;
  
private:
  void UpdateCamera3D();
  
  Vector3 m_target = {0, 0, 0};
  float m_yaw = 0.f;
  float m_pitch = 0.f;
  float m_rotation_speed = 2.0f;
  float m_radius = 10.f;
};
