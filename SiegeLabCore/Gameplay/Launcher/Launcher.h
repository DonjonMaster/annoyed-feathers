#pragma once
#include "ShotSettings.h"
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class Launcher
{
public:
  void Aim(const InputSnapshot& _input);
  
  // Get shot settings made of Launcher's settings
  ShotSettings GetShotSettings() const;
  
  // Change rotation or speed
  void SetYaw(float _yaw);
  void SetPitch(float _pitch);
  void SetSpeed(int _speed);

  // Get rotation or speed
  float GetYaw() const { return m_yaw; }
  float GetPitch() const { return m_pitch; }
  int GetSpeed() const { return m_speed; }

private:
  int m_speed = 12;
  float m_yaw = 0.f;
  float m_pitch = 30.f;
  ProjectileKind m_kind = ProjectileKind::kStandard;
};
