#include "Launcher.h"

#include <algorithm>
#include <iostream>

#include <raymath.h>

void Launcher::Aim(const InputSnapshot& _input)
{
  int yaw_direction = 0;
  if (_input.IsPressed(InputButton::kLauncherLeft))
  {
    std::printf("Launcher goes left");
    yaw_direction -= 1;
  }
  if (_input.IsPressed(InputButton::kLauncherRight)) yaw_direction += 1;

  int pitch_direction = 0;
  if (_input.IsPressed(InputButton::kLauncherUp)) pitch_direction += 1;
  if (_input.IsPressed(InputButton::kLauncherDown)) pitch_direction -= 1;

  int delta_speed = 0;
  if (_input.IsPressed(InputButton::kLauncherSpeedUp)) delta_speed += 1;
  if (_input.IsPressed(InputButton::kLauncherSpeedDown)) delta_speed -= 1;

  // Apply new values if necessary
  if (yaw_direction != 0)
    SetYaw(m_yaw + static_cast<float>(m_speed * yaw_direction));

  if (pitch_direction != 0)
    SetPitch(m_pitch + static_cast<float>(m_speed * pitch_direction));

  if (delta_speed != 0)
    SetSpeed(m_speed + delta_speed);

  // Change kind if an input is pressed
  if (_input.IsPressed(InputButton::kLauncherSelectKindStandard))
    m_kind = ProjectileKind::kStandard;
  if (_input.IsPressed(InputButton::kLauncherSelectKindHeavy))
    m_kind = ProjectileKind::kHeavy;
}

ShotSettings Launcher::GetShotSettings() const
{
  const float a = m_yaw * DEG2RAD;
  const float e = m_pitch * DEG2RAD;

  // Direction made of azimuth (yaw) and elevations (pitch)
  cyclone::Vector3 direction =
  {
    cosf(e) * cosf(a),
    sinf(e),
    cosf(e) * sinf(a)
  };

  direction.normalise();

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
