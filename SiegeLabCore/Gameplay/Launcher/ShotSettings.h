#pragma once
#include <raylib.h>

enum class ProjectileKind
{
  kStandard,
  kHeavy,
};

struct ShotSettings
{
  Vector3 origin;
  Vector3 direction;
  int speed;
  ProjectileKind kind;
};
