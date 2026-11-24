#pragma once
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"
#include "SiegeLabCore/Gameplay/Launcher/ShotSettings.h"

class Projectile : public GameEntity
{
public:
  void Fire(ShotSettings settings);
  void RegisterPhysics(PhysicsWorld world) override;
  void Draw() override;

private:
  cyclone::CollisionSphere sphere_;
};
