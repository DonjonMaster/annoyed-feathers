#pragma once
#include <array>
#include <functional>
#include <vector>

#include "PhysicsRegistration.h"
#include "CollisionEvents/CollisionEventDispatcher.h"
#include "CollisionEvents/CollisionEventGenerator.h"
#include "Cyclone/include/collide_fine.h"
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"

class PhysicsWorld
{
public:
  PhysicsWorld();
  
  void RegisterSphere(EntityId id, cyclone::RigidBody& body,
                      cyclone::CollisionSphere& sphere);
  void RegisterBox(EntityId id, cyclone::RigidBody& body,
                   cyclone::CollisionBox& box);
  void RegisterPlane(cyclone::CollisionPlane plane);
  void UnregisterObject(EntityId id);
  cyclone::CollisionData createCollisionData();
  void Step(float dt, bool _integrates = true);
  void Reset();
  
private:
  void GameEntitiesCollisions(cyclone::CollisionData& data, bool& coverageComplete);
  void PlanesCollisions(cyclone::CollisionData& data, bool& coverageComplete);
  void AfterContact();
  void BeforeContact();
  void Integrate(float dt);
  
  void CopyPreparedContacts(const cyclone::Contact* contacts, unsigned count);
  
  bool TryGetEndpoint(cyclone::RigidBody* body, 
    CollisionEndpoint& result) const;
  
  std::vector<PhysicsRegistration> registrations_;
  std::vector<cyclone::CollisionPlane> planes_;
  
  // Contacts
  std::vector<ContactSnapshot> snapshots_;
  CollisionEventGenerator eventGenerator_;
  CollisionEventDispatcher eventDispatcher_;

  
  static const unsigned MaxContacts = 1024;
  
  std::array<cyclone::Contact, MaxContacts> contactBuffer_{};
  cyclone::ContactResolver resolver_ = cyclone::ContactResolver(1);
};
