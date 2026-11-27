#pragma once
#include "CollisionEvent.h"

class ICollisionListener
{
public:
  virtual ~ICollisionListener() = default;
  virtual void OnCollision(CollisionEvent event);
};
