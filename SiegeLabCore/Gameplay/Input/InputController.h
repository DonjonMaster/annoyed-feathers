#pragma once

#include <cstddef>

#include "build/external/raylib-master/src/raylib.h"
#include <bitset>

enum class InputButton
{
  Orbit,
  YawLeft,
  YawRight,
  PitchUp,
  PitchDown,
  Count,
};

struct InputSnapshot
{
  // Only for buttons inputs, not analog inputs
  std::bitset<static_cast<std::size_t>(InputButton::Count)>buttons;
  
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
  InputSnapshot capture();
};
