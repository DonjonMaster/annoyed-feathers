#include "ICameraController.h"

void ICameraController::Update(const InputSnapshot& input, float dt)
{
  if (input.isDown(InputButton::Orbit))
  {
    camera_.yaw += input.mouseDelta.x;
    camera_.pitch -= input.mouseDelta.y;
  }
  const float yawAxis =
    static_cast<float>(input.isDown(InputButton::YawRight)) -
    static_cast<float>(input.isDown(InputButton::YawLeft));
  const float pitchAxis =
    static_cast<float>(input.isDown(InputButton::PitchUp)) -
    static_cast<float>(input.isDown(InputButton::PitchDown));
  camera_.yaw += yawAxis * camera_.rotationSpeed * dt;
  camera_.pitch += pitchAxis * camera_.rotationSpeed * dt;
}