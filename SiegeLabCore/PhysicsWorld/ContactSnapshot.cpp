#include "ContactSnapshot.h"

#include <concepts>

CollisionEndpoint CollisionEndpoint::Entity(EntityId id)
{
  CollisionEndpoint result;
  result.entity = id;
  return result;
}

CollisionEndpoint CollisionEndpoint::WorldGround()
{
  CollisionEndpoint result;
  result.isWorldGround = true;
  return result;
}

bool CollisionEndpoint::operator==(const CollisionEndpoint& other) const
{
  if (isWorldGround != other.isWorldGround)
    return false;
  
  if (isWorldGround)
    return true;
  
  return entity.slot == other.entity.slot && 
    entity.generation == other.entity.generation;
}

bool CollisionEndpoint::operator<(const CollisionEndpoint& other) const
{
  if (isWorldGround != other.isWorldGround)
    return isWorldGround;
  
  if (isWorldGround)
    return false;
  
  if (entity.slot != other.entity.slot)
    return entity.slot < other.entity.slot;
  
  return entity.generation < other.entity.generation;
}

// Link the two collisions points
CollisionPairKey CollisionPairKey::Make(
  CollisionEndpoint first, 
  CollisionEndpoint second)
{
  if (second < first)
    std::ranges::swap(first, second);
  
  return {first, second};
}

bool CollisionPairKey::operator<(const CollisionPairKey& other) const
{
  if (a == other.a)
    return b < other.b;
  
  return a < other.a;
}
