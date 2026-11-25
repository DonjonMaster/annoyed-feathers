#pragma once
#include "ShotSettings.h"
#include "SiegeLabCore/Gameplay/Input/InputController.h"

class Launcher
{
public:
  void Aim(InputSnapshot& input);
  ShotSettings GetShotSettings();
  
  void SetYaw(float _yaw);
  void SetPitch(float _pitch);
  void SetSpeed(int _speed);
  
  float GetYaw() { return yaw; }
  float GetPitch() { return pitch; }
  int GetSpeed() { return speed; }
  
private:
  int speed = 12;
  float yaw = 0.f;
  float pitch = 30.f;
  
  /*  0 = StandardProjectile
   *  1 = HeavyProjectile */
  int kind = 0;
};
