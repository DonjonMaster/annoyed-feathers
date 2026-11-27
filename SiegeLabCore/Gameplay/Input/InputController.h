#pragma once

#include <cstddef>

#include "build/external/raylib-master/src/raylib.h"
#include <bitset>

enum class InputButton
{
  // Camera
  kOrbit,
  kYawLeft,
  kYawRight,
  kPitchUp,
  kPitchDown,

  // Launcher
  kLauncherUp,
  kLauncherDown,
  kLauncherLeft,
  kLauncherRight,
  kLauncherSpeedUp,
  kLauncherSpeedDown,
  kLauncherSelectKindHeavy,
  kLauncherSelectKindStandard,
  
  // Global
  kCount,
};

using InputBitset = std::bitset<static_cast<std::size_t>(InputButton::kCount)>;

struct InputSnapshot
{
  // Only for buttons inputs, not analog inputs
  InputBitset buttons;
  InputBitset pressed_buttons;

  // For analog input, still use floats
  Vector2 mouse_delta {};
  float wheel_delta = 0.0f;

  bool IsDown(InputButton _button) const
  {
    return buttons.test(static_cast<std::size_t>(_button));
  }
  
  bool IsPressed(InputButton _button) const
  {
    return pressed_buttons.test(static_cast<std::size_t>(_button));
  }
  
  
};

class InputController
{
public:
  InputSnapshot Capture();

private:
  InputBitset m_previous_frame_buttons;
  
  void CaptureCameraInputs(InputSnapshot& _input);
  void CaptureLauncherInputs(InputSnapshot& _input);
};
