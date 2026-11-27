#pragma once
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"
#include "SiegeLabCore/Gameplay/Launcher/ShotSettings.h"

class Projectile : public GameEntity
{
  friend class TrajectoryPredictor;
  
public:
  Projectile();
  
  void Fire(ShotSettings _settings);
  void RegisterPhysics(PhysicsWorld& _world) override;
  void Draw() override {}

protected:
  cyclone::CollisionSphere sphere_;
};
