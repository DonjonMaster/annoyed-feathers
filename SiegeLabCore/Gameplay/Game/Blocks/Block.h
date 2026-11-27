#pragma once
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

class Block : public GameEntity
{
public:
  Block(cyclone::Vector3 _pos);
  void RegisterPhysics(PhysicsWorld& world) override;
  void Draw() override;

protected:
  cyclone::CollisionBox box_;
};
