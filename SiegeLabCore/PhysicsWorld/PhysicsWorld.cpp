#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld()
{
  resolver_.setPreparedContactObserver([this](const cyclone::Contact* contacts, unsigned count)
  {
    CopyPreparedContacts(contacts, count);
  });
}

void PhysicsWorld::RegisterSphere(EntityId id, cyclone::RigidBody& body,
                                  cyclone::CollisionSphere& sphere)
{
  registrations_.push_back({id, &body, &sphere, nullptr, kSphere});
}

void PhysicsWorld::RegisterBox(EntityId id, cyclone::RigidBody& body,
  cyclone::CollisionBox& box)
{
  registrations_.push_back({id, &body, nullptr, &box, kBox});
}

void PhysicsWorld::RegisterPlane(cyclone::CollisionPlane plane)
{
  planes_.push_back(plane);
}

void PhysicsWorld::UnregisterObject(EntityId id)
{
  std::erase_if(registrations_,
                [id](const PhysicsRegistration& r)
                {
                  return r.entityId.slot == id.slot && r.entityId.generation ==
                    id.generation;
                });
  
  eventGenerator_.RemoveEndpoint(CollisionEndpoint::Entity(id));
}

void PhysicsWorld::GameEntitiesCollisions(cyclone::CollisionData& data, bool& coverageComplete)
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
      
      if (!data.hasMoreContacts())
      {
        return;
      }
      
      if (
          !(a.collision_sphere || a.collision_box) ||
          !(b.collision_sphere || b.collision_box)
      )
        continue;
      
      if (a.collision_sphere && b.collision_sphere)
      {
          cyclone::CollisionDetector::sphereAndSphere(
            *a.collision_sphere, *b.collision_sphere, &data);
      }
      else if (a.collision_sphere && b.collision_box)
      {
          cyclone::CollisionDetector::boxAndSphere(
            *b.collision_box, *a.collision_sphere, &data);
      }
      else if (a.collision_box && b.collision_sphere)
      {
          cyclone::CollisionDetector::boxAndSphere(
            *a.collision_box, *b.collision_sphere, &data);
      }
      else if (a.collision_box && b.collision_box)
      {
          cyclone::CollisionDetector::boxAndBox(
            *a.collision_box, *b.collision_box, &data);
      }
    }
  }
}

void PhysicsWorld::PlanesCollisions(cyclone::CollisionData& data, bool& coverageComplete)
{
  for (auto& r : registrations_)
  {
    if (r.body->getInverseMass() <= 0)
      continue;
    
    if (!data.hasMoreContacts())
    {
      return;
    }
    
    for (auto plane : planes_)
    {
      if (r.collision_sphere)
      {
          cyclone::CollisionDetector::sphereAndHalfSpace(
            *r.collision_sphere, plane, &data);
      }
      else if (r.collision_box)
      {
          cyclone::CollisionDetector::boxAndHalfSpace(
            *r.collision_box, plane, &data);
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

void PhysicsWorld::CopyPreparedContacts(const cyclone::Contact* contacts,
  unsigned count)
{
  for (unsigned i = 0; i < count; ++i)
  {
    const cyclone::Contact& contact = contacts[i];

    ContactSnapshot snapshot;

    if (!TryGetEndpoint(contact.body[0], snapshot.a) ||
        !TryGetEndpoint(contact.body[1], snapshot.b))
    {
      continue;
    }

    snapshot.point = contact.contactPoint;
    snapshot.normal = contact.contactNormal;
    snapshot.closingSpeed = contact.getClosingSpeed();

    if (snapshot.b < snapshot.a)
    {
      std::swap(snapshot.a, snapshot.b);
      snapshot.normal *= -1.0f;
    }

    snapshots_.push_back(snapshot);
  }
}

bool PhysicsWorld::TryGetEndpoint(cyclone::RigidBody* body,
                                  CollisionEndpoint& result) const
{
  if (body == nullptr)
  {
    result = CollisionEndpoint::WorldGround();
    return true;
  }
  
  for (const PhysicsRegistration registration : registrations_)
  {
    if (registration.body == body)
    {
      result = CollisionEndpoint::Entity(registration.entityId);
      return true;
    }
  }
  
  return false;
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

void PhysicsWorld::Step(const float dt, const bool _integrates)
{
  if (dt <= 0)
    return;
  
  snapshots_.clear();
  bool coverageComplete = true;

  // Integrate only movable bodies
  if (_integrates)
    Integrate(dt);

  // Refresh collider transforms before detection
  BeforeContact();

  cyclone::CollisionData data = createCollisionData();

  // GameEntities collisions
  GameEntitiesCollisions(data, coverageComplete);

  // Collisions with planes
  PlanesCollisions(data, coverageComplete);

  // Resolve contacts
  if (data.contactCount > 0)
    resolver_.resolveContacts(data.contactArray, data.contactCount, dt);
  
  if (data.contactCount > 0)
    resolver_.resolveContacts(data.contacts, data.contactCount, dt);

  // Refresh the GameEntities data
  AfterContact();
  
  auto events = eventGenerator_.Generate(snapshots_, coverageComplete);
  
  eventDispatcher_.Publish(events);
}

void PhysicsWorld::Reset()
{
  snapshots_.clear();
  eventGenerator_.Reset();
}
