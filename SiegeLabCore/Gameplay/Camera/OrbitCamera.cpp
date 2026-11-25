#include "OrbitCamera.h"

void OrbitCamera::Update(const InputSnapshot& input, float dt)
{
  if (input.isDown(InputButton::Orbit))
  {
    yaw += input.mouseDelta.x;
    pitch -= input.mouseDelta.y;
  }
  const float yawAxis =
    static_cast<float>(input.isDown(InputButton::YawRight)) -
    static_cast<float>(input.isDown(InputButton::YawLeft));
  const float pitchAxis =
    static_cast<float>(input.isDown(InputButton::PitchUp)) -
    static_cast<float>(input.isDown(InputButton::PitchDown));
  yaw += yawAxis * rotationSpeed * dt;
  pitch += pitchAxis * rotationSpeed * dt;
}