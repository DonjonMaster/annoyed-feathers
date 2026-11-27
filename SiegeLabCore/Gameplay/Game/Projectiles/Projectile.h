#pragma once
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"
#include "SiegeLabCore/Gameplay/Launcher/ShotSettings.h"

class Projectile : public GameEntity
{
  friend class TrajectoryPredictor;
  
public:
  Projectile();
  
  void Fire(ShotSettings settings);
  void RegisterPhysics(PhysicsWorld& world) override;
  void Draw() override {}

protected:
  cyclone::CollisionSphere sphere_;
};
