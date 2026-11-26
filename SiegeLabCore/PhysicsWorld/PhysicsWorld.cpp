#include "PhysicsWorld.h"

void PhysicsWorld::RegisterSphere(EntityId id, cyclone::RigidBody& body,
  cyclone::CollisionSphere& sphere)
{
  registrations_.push_back({id, &body, &sphere, kSphere});
}

void PhysicsWorld::RegisterBox(EntityId id, cyclone::RigidBody& body,
  cyclone::CollisionBox& box)
{
  registrations_.push_back({id, &body, &box, kBox});
}

void PhysicsWorld::RegisterPlane(cyclone::CollisionPlane plane)
{
  planes_.push_back(&plane);
}

void PhysicsWorld::UnregisterObject(EntityId id)
{
  std::erase_if(registrations_,
                [id](const PhysicsRegistration& r)
                {
                  return r.entityId.slot == id.slot && r.entityId.generation ==
                    id.generation;
                });
}

void PhysicsWorld::GameEntitiesCollisions(cyclone::CollisionData data, <lambda bool()> canDetect)
{
  for (std::size_t i = 0; i < registrations_.size(); ++i)
  {
    auto& a = registrations_[i];
    
    for (std::size_t j = i + 1; j < registrations_.size(); ++j)
    {
      auto& b = registrations_[j];
      
      const bool aFixed = a.body->getInverseMass() <= 0;
      const bool bFixed = b.body->getInverseMass() <= 0;
      if (aFixed && bFixed)
        continue;
      
      if (a.collision_sphere && b.collision_sphere)
      {
        if (canDetect())
          cyclone::CollisionDetector::sphereAndSphere(
            *a.collision_sphere, *b.collision_sphere, &data);
      }
      else if (a.collision_sphere && b.collision_box)
      {
        if (canDetect())
          cyclone::CollisionDetector::boxAndSphere(
            *b.collision_box, *a.collision_sphere, &data);
      }
      else if (a.collision_box && b.collision_sphere)
      {
        if (canDetect())
          cyclone::CollisionDetector::boxAndSphere(
            *a.collision_box, *b.collision_sphere, &data);
      }
      else if (a.collision_box && b.collision_box)
      {
        if (canDetect())
          cyclone::CollisionDetector::boxAndBox(
            *a.collision_box, *b.collision_box, &data);
      }
    }
  }
}

void PhysicsWorld::PlanesCollisions(cyclone::CollisionData data, <lambda bool()> canDetect)
{
  for (auto& r : registrations_)
  {
    if (r.body->getInverseMass() <= 0)
      continue;
    
    for (auto* plane : planes_)
    {
      if (r.collision_sphere)
      {
        if (canDetect())
          cyclone::CollisionDetector::sphereAndHalfSpace(
            *r.collision_sphere, *plane, &data);
      }
      else if (r.collision_box)
      {
        if (canDetect())
          cyclone::CollisionDetector::boxAndHalfSpace(
            *r.collision_box, *plane, &data);
      }
    }
  }
}

void PhysicsWorld::AfterContact()
{
  for (auto& r : registrations_)
  {
    r.body->calculateDerivedData();
    
    if (r.collision_sphere)
      r.collision_sphere->calculateInternals();
    else if (r.collision_box)
      r.collision_box->calculateInternals();
  }
}

void PhysicsWorld::BeforeContact()
{
  for (auto& r : registrations_)
  {
    if (r.collision_sphere)
      r.collision_sphere->calculateInternals();
    else if (r.collision_box)
      r.collision_box->calculateInternals();
  }
}

void PhysicsWorld::Integrate(float dt)
{
  for (auto& r : registrations_)
  {
    if (r.body && r.body->getInverseMass() > 0)
      r.body->integrate(dt);
  }
}

cyclone::CollisionData PhysicsWorld::createCollisionData()
{
  cyclone::CollisionData data;
  data.contactArray = contactBuffer_.data();
  data.reset(static_cast<unsigned>(contactBuffer_.size()));
  data.friction = 0.8;
  data.restitution = 0.2;
  data.tolerance = 0.1;
  return data;
}

void PhysicsWorld::Step(const float dt)
{
  if (dt <= 0)
    return;

  // Integrate only movable bodies
  Integrate(dt);

  // Refresh collider transforms before detection
  BeforeContact();

  cyclone::CollisionData data = createCollisionData();

  bool coverageIncomplete = false;

  auto canDetect = [&]()
  {
    if (data.hasMoreContacts())
      return true;

    coverageIncomplete = true;
    return false;
  };

  // GameEntities collisions
  GameEntitiesCollisions(data, canDetect);

  // Collisions with planes
  PlanesCollisions(data, canDetect);

  // Resolve contacts
  if (data.contactCount > 0)
    resolver_.resolveContacts(data.contactArray, data.contactCount, dt);

  // Refresh the GameEntities data
  AfterContact();
}

void PhysicsWorld::Reset()
{
}
