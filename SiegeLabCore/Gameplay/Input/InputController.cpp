#include "InputController.h"

InputSnapshot InputController::capture()
{
  InputSnapshot input;
  
  input.buttons.set(
    static_cast<std::size_t>(InputButton::Orbit),
    IsMouseButtonDown(MOUSE_BUTTON_RIGHT));
  
  input.buttons.set(
    static_cast<std::size_t>(InputButton::YawLeft),
    IsKeyDown(KEY_LEFT));
  
  input.buttons.set(
    static_cast<std::size_t>(InputButton::YawRight),
    IsKeyDown(KEY_RIGHT));
  
  input.buttons.set(
    static_cast<std::size_t>(InputButton::PitchUp),
    IsKeyDown(KEY_UP));
  
  input.buttons.set(
    static_cast<std::size_t>(InputButton::PitchDown),
    IsKeyDown(KEY_DOWN));
  
  if (input.isDown(InputButton::Orbit))
  {
    input.mouseDelta = GetMouseDelta();
  }
  
  input.wheelDelta = GetMouseWheelMove();
  return input;
}
