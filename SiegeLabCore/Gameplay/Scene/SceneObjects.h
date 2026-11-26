#pragma once
#include <vector>

#include "EntityId.h"
#include "ObjectPool.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

class SceneObjects
{
public:
  template <typename T, typename... Args>
  EntityId CreateEntity(Args&&... args)
  {
    return pool_.Create<T>(std::forward<Args>(args)...);
  }

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
