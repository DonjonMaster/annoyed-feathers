#pragma once
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

class Block : public GameEntity
{
public:
  Block(const cyclone::Vector3& _pos);
  void RegisterPhysics(PhysicsWorld& _world) override;
  void Draw() override;

protected:
  cyclone::CollisionBox m_box_;
};
