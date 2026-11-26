#pragma once
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

class Block : public GameEntity
{
public:
  void RegisterPhysics(PhysicsWorld& world) override;
  void Draw() override;

private:
  cyclone::CollisionBox box_;
};
