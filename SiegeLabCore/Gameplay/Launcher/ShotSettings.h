#pragma once

#include "core.h"

enum class ProjectileKind
{
  kStandard,
  kHeavy,
};

struct ShotSettings
{
  cyclone::Vector3 origin;
  cyclone::Vector3 direction;
  int speed;
  ProjectileKind kind;
};
