#include "OrbitCamera.h"

#include <cmath>

void OrbitCamera::Update(const InputSnapshot& input, float dt)
{
  const float yawAxis =
        static_cast<float>(input.isDown(InputButton::kYawRight)) -
        static_cast<float>(input.isDown(InputButton::kYawLeft));

  const float pitchAxis =
      static_cast<float>(input.isDown(InputButton::kPitchUp)) -
      static_cast<float>(input.isDown(InputButton::kPitchDown));
  
  yaw += yawAxis * rotationSpeed * dt;
  pitch += pitchAxis * rotationSpeed * dt;
  
  if (input.isDown(InputButton::kOrbit))
  {
    yaw += input.mouseDelta.x;
    pitch -= input.mouseDelta.y;
  }
  
  position = Position();
  Camera3D::target = target;
  up = {0, 1, 0};
  fovy = 45.0f;
  projection = CAMERA_PERSPECTIVE;
}

Vector3 OrbitCamera::Position() const
{
  const float y = yaw * DEG2RAD;
  const float p = pitch * DEG2RAD;
  
  return {
    target.x + radius * std::cos(p) * std::sin(y),
    target.y + radius * std::sin(p),
    target.z + radius * std::cos(p) * std::cos(y)
  };
}
