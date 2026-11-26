#include "Launcher.h"

#include <algorithm>

#include <raymath.h>

void Launcher::Aim(const InputSnapshot& _input)
{
  int yaw_direction = 0;
  if (_input.isDown(InputButton::kLauncherLeft)) yaw_direction -= 1;
  if (_input.isDown(InputButton::kLauncherRight)) yaw_direction += 1;

  int pitch_direction = 0;
  if (_input.isDown(InputButton::kLauncherUp)) pitch_direction += 1;
  if (_input.isDown(InputButton::kLauncherDown)) pitch_direction -= 1;

  int delta_speed = 0;
  if (_input.isDown(InputButton::kLauncherSpeedUp)) delta_speed += 1;
  if (_input.isDown(InputButton::kLauncherSpeedDown)) delta_speed -= 1;

  // Apply new values if necessary
  if (yaw_direction != 0)
    SetYaw(m_yaw + static_cast<float>(m_speed * yaw_direction));

  if (pitch_direction != 0)
    SetPitch(m_pitch + static_cast<float>(m_speed * pitch_direction));

  if (delta_speed != 0)
    SetSpeed(m_speed + delta_speed);

  // Change kind if an input is pressed
  if (_input.isDown(InputButton::kLauncherSelectKindStandard)) m_kind = 0;
  if (_input.isDown(InputButton::kLauncherSelectKindHeavy)) m_kind = 1;
}

ShotSettings Launcher::GetShotSettings() const
{
  const float a = m_yaw * DEG2RAD;
  const float e = m_pitch * DEG2RAD;

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
  shot_settings.origin = {0, 0, 0};
  shot_settings.direction = direction;
  shot_settings.speed = m_speed;
  shot_settings.kind = m_kind;

  return shot_settings;
}

void Launcher::SetYaw(const float _yaw)
{
  m_yaw = std::clamp(_yaw, -30.f, 30.f);
}

void Launcher::SetPitch(const float _pitch)
{
  m_pitch = std::clamp(_pitch, 5.f, 55.f);
}

void Launcher::SetSpeed(const int _speed)
{
  m_speed = std::clamp(_speed, 8, 22);
}
