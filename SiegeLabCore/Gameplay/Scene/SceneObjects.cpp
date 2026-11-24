#include "SceneObjects.h"

GameEntity* SceneObjects::Get(const EntityId id)
{
  return pool_.Get(id);
}

void SceneObjects::RequestRemove(EntityId id)
{
  for (auto removal : removals_)
    if (
      id.slot == removal.slot &&
      id.generation == removal.generation
    )
      return;
  removals_.push_back(id);
}

void SceneObjects::FlushRemovals()
{
  for (auto removal : removals_)
    pool_.Destroy(removal);
}
