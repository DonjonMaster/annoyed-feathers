#include "Launcher.h"

#include <algorithm>
#include <raymath.h>

void Launcher::Aim(InputSnapshot& input)
{
  int yaw_direction = 0;
  int pitch_direction = 0;
  int delta_speed = 0;
  
  // Apply new values
  SetYaw(yaw + static_cast<float>(speed * yaw_direction));
  SetPitch(pitch + static_cast<float>(speed * pitch_direction));
  SetSpeed(speed + delta_speed);
  
  // TODO: If 1/2 input is pressed, change projectile_kind
}

ShotSettings Launcher::GetShotSettings()
{
  const float a = yaw * DEG2RAD;
  const float e = pitch * DEG2RAD;
  
  // Direction made of azimuth (yaw) and elevations (pitch)
  Vector3 direction =
  {
    cosf(e) * cosf(a),
    sinf(e),
    cosf(e) * sinf(a)
  }; 
  
  direction = Vector3Normalize(direction);
  
  // Make shot settings :)
  ShotSettings shot_settings;
  shot_settings.origin = { 0, 0, 0 };
  shot_settings.direction = direction;
  shot_settings.speed = speed;
  shot_settings.kind = kind;
  
  return shot_settings;
}

void Launcher::SetYaw(float _yaw)
{
  yaw = std::clamp(_yaw, -30.f, 30.f);
}

void Launcher::SetPitch(float _pitch)
{
  pitch = std::clamp(_pitch, 5.f, 55.f);
}

void Launcher::SetSpeed(int _speed)
{
  speed = std::clamp(_speed, 8, 22);
}
