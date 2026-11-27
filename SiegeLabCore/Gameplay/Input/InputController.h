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

struct InputSnapshot
{
  // Only for buttons inputs, not analog inputs
  std::bitset<static_cast<std::size_t>(InputButton::kCount)> buttons;

  // For analog input, still use floats
  Vector2 mouseDelta{};
  float wheelDelta = 0.0f;

  bool isDown(InputButton button) const
  {
    return buttons.test(static_cast<std::size_t>(button));
  }
};

class InputController
{
public:
  InputSnapshot Capture();

private:
  void CaptureCameraInputs(InputSnapshot& _input);
  void CaptureLauncherInputs(InputSnapshot& _input);
};
