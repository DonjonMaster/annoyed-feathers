#pragma once
#include "EntityId.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

#include <memory>
#include <vector>

class SceneObjects
{
public:
  template<typename T>
  EntityId CreateEntity();
  GameEntity* Get(int id);
  void FlushRemovals();
  
private:
  std::vector<std::unique_ptr<GameEntity*>> entities_;
};
