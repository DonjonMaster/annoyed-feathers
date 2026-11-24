#pragma once
#include <vector>

#include "EntityId.h"
#include "ObjectPool.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

class SceneObjects
{
public:
  template<typename T>
  EntityId CreateEntity() { pool_.Create<T>(); }
  
  // Get a GameEntity from an EntityId
  GameEntity* Get(EntityId id);
  
  // Request remove of an entity with corresponding EntityId
  void RequestRemove(EntityId id);
  
  // Flush removals from pool
  void FlushRemovals();
  
private:
  ObjectPool<GameEntity, 32> pool_;
  std::vector<EntityId> removals_;
};

