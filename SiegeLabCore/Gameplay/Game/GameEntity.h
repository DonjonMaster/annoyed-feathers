#pragma once
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"
#include "SiegeLabCore/PhysicsWorld/PhysicsWorld.h"

class GameEntity
{
  friend class SceneObjects;
  
public:
  virtual ~GameEntity() = default;
  virtual void ConfigurePhysics() {}
  virtual void RegisterPhysics(PhysicsWorld& world) {}
  virtual void Draw() {}
  
  cyclone::RigidBody& GetBody() {return  body_;}
  
protected:
  EntityId id_;
  cyclone::RigidBody body_;
};
