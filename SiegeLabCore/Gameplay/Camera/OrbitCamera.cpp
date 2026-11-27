#include "OrbitCamera.h"

#include <cmath>

void OrbitCamera::Update(const InputSnapshot& _input, float _dt)
{
  const float yawAxis =
    static_cast<float>(_input.IsDown(InputButton::kYawRight)) -
    static_cast<float>(_input.IsDown(InputButton::kYawLeft));

  const float pitchAxis =
    static_cast<float>(_input.IsDown(InputButton::kPitchUp)) -
    static_cast<float>(_input.IsDown(InputButton::kPitchDown));

  m_yaw += yawAxis * m_rotation_speed * _dt;
  m_pitch += pitchAxis * m_rotation_speed * _dt;

  if (_input.IsDown(InputButton::kOrbit))
  {
    m_yaw += _input.mouse_delta.x;
    m_pitch -= _input.mouse_delta.y;
  }
  
  UpdateCamera3D();
}

Vector3 OrbitCamera::GetPosition() const
{
  const float y = m_yaw * DEG2RAD;
  const float p = m_pitch * DEG2RAD;

  return {
    m_target.x + m_radius * std::cos(p) * std::sin(y),
    m_target.y + m_radius * std::sin(p),
    m_target.z + m_radius * std::cos(p) * std::cos(y)
  };
}

void OrbitCamera::UpdateCamera3D()
{
  const float y = m_yaw * DEG2RAD;
  const float p = m_pitch * DEG2RAD;
  
  Camera3D::position = GetPosition();
  Camera3D::target = m_target;
  Camera3D::up = {
    -std::sin(p) * std::sin(y),
     std::cos(p),
    -std::sin(p) * std::cos(y)
  };
  
  Camera3D::fovy = 45.f;
  Camera3D::projection = CAMERA_PERSPECTIVE;
}
