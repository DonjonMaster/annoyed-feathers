#include "InputController.h"

InputSnapshot InputController::capture()
{
  InputSnapshot input;
  CaptureCameraInputs(input);
  CaptureLauncherInputs(input);

  if (input.isDown(InputButton::kOrbit))
  {
    input.mouseDelta = GetMouseDelta();
  }

  input.wheelDelta = GetMouseWheelMove();
  return input;
}

void InputController::CaptureCameraInputs(InputSnapshot& _input)
{
  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kOrbit),
    IsMouseButtonDown(MOUSE_BUTTON_RIGHT));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kYawLeft),
    IsKeyDown(KEY_LEFT));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kYawRight),
    IsKeyDown(KEY_RIGHT));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kPitchUp),
    IsKeyDown(KEY_UP));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kPitchDown),
    IsKeyDown(KEY_DOWN));
}

void InputController::CaptureLauncherInputs(InputSnapshot& _input)
{
  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherLeft),
    IsKeyDown(KEY_A));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherRight),
    IsKeyDown(KEY_D));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherUp),
    IsKeyDown(KEY_W));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherDown),
    IsKeyDown(KEY_S));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherSpeedUp),
    IsKeyDown(KEY_Q));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherSpeedDown),
    IsKeyDown(KEY_E));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherSelectKindStandard),
    IsKeyDown(KEY_ONE));

  _input.buttons.set(
    static_cast<std::size_t>(InputButton::kLauncherSelectKindHeavy),
    IsKeyDown(KEY_TWO));
}
