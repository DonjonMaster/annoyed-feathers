#pragma once
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"
#include "SiegeLabCore/PhysicsWorld/PhysicsWorld.h"

class GameEntity
{
  friend class SceneObjects;
  
public:
  virtual ~GameEntity() = default;
  virtual void ConfigurePhysics() {}
  virtual void RegisterPhysics(PhysicsWorld& _world) {}
  virtual void Draw() {}
  
  cyclone::RigidBody& GetBody() {return  m_body_;}
  
protected:
  EntityId m_id_;
  cyclone::RigidBody m_body_;
};
