#pragma once
#include <vector>

#include "EntityId.h"
#include "ObjectPool.h"
#include "SiegeLabCore/Gameplay/Game/GameEntity.h"

class SceneObjects
{
public:
  template<typename T, typename... Args>
  EntityId CreateEntity(Args&&... args)
  {
    EntityId id = pool_.Create<T>(std::forward<Args>(args)...);
    
    GameEntity* game_entity = Get(id);
    game_entity->id_ = id;
    game_entity->ConfigurePhysics();
    game_entity->RegisterPhysics(world);
    
    return id;
  }
  
  // Get a GameEntity from an EntityId
  GameEntity* Get(EntityId id);

  // Request remove of an entity with corresponding EntityId
  void RequestRemove(EntityId id);

  // Flush removals from pool
  void FlushRemovals();

  static SceneObjects* GetInstance()
  {
    if (!m_instance)
      m_instance = new SceneObjects();
    return m_instance;
  }
  
  PhysicsWorld& GetPhysicsWorld() { return world; }
  std::vector<GameEntity*>& GetGameEntities() { return pool_.GetObjects(); }
  
private:
  static SceneObjects* m_instance;
  ObjectPool<GameEntity, 32> pool_;
  std::vector<EntityId> removals_;
  PhysicsWorld world;
};
