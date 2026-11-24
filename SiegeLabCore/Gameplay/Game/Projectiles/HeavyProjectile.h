#pragma once
#include "Projectile.h"

class HeavyProjectile : Projectile
{
public:
  void ConfigurePhysics() override;
};
