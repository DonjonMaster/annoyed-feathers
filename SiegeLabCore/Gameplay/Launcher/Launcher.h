#pragma once
#include "ShotSettings.h"

class Launcher
{
public:
  void Aim(/* TODO: InputSnapshot snapshot */);
  ShotSettings GetShotSettings();
  
  void SetYaw(float _yaw);
  void SetPitch(float _pitch);
  void SetSpeed(int _speed);
  
private:
  int speed = 12;
  float yaw = 0.f;
  float pitch = 30.f;
  
  /*  0 = StandardProjectile
   *  1 = HeavyProjectile */
  int kind = 0;
};
