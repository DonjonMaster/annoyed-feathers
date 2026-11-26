#pragma once
#include "SiegeLabCore/PhysicsWorld/PhysicsWorld.h"

class GameEntity
{
public:
  virtual ~GameEntity() = default;

  virtual void ConfigurePhysics()
  {
  }

  virtual void RegisterPhysics(PhysicsWorld world)
  {
  }

  virtual void Draw()
  {
  }
};
