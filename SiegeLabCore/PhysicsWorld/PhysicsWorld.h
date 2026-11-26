#pragma once
#include <array>
#include <vector>

#include "PhysicsRegistration.h"
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"

class PhysicsWorld
{
public:
  void RegisterSphere(EntityId id, cyclone::RigidBody& body,
                      cyclone::CollisionSphere& sphere);
  void RegisterBox(EntityId id, cyclone::RigidBody& body,
                   cyclone::CollisionBox& box);
  void RegisterPlane(cyclone::CollisionPlane plane);
  void UnregisterObject(EntityId id);
  cyclone::CollisionData createCollisionData();
  void Step(const float dt);
  void Reset();
private:
  void GameEntitiesCollisions(cyclone::CollisionData data,
                              __resharper_unknown_type, bool(),
                              __resharper_unknown_type);
  void PlanesCollisions(cyclone::CollisionData data, __resharper_unknown_type,
                        bool(), __resharper_unknown_type);
  void AfterContact();
  void BeforeContact();
  void Integrate(float dt);
  
  std::vector<PhysicsRegistration> registrations_;
  std::vector<cyclone::CollisionPlane*> planes_;
  
  static const unsigned MaxContacts = 1024;
  
  std::array<cyclone::Contact, MaxContacts> contactBuffer_{};
  cyclone::ContactResolver resolver_;
};
