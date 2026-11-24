#pragma once
#include <vector>

#include "EntityId.h"
#include "ObjectPool.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

class SceneObjects
{
public:
  template<typename T>
  EntityId CreateEntity();
  GameEntity* Get(int id);
  void FlushRemovals();
  
private:
  ObjectPool<GameEntity*, 32> pool_;
};

template <typename T>
EntityId SceneObjects::CreateEntity()
{
  pool_.Create<T>();
}

