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
  for (EntityId id : removals_)
  {
    if (GameEntity* entity = Get(id))
    {
      world.UnregisterObject(id);
      pool_.Destroy(id);
    }
  }
  removals_.clear();
}
