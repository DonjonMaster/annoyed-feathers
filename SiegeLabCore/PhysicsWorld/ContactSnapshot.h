#pragma once
#include "Cyclone/include/body.h"
#include "SiegeLabCore/Gameplay/Scene/EntityId.h"

struct CollisionEndpoint
{
  bool isWorldGround = false;
  EntityId entity{};

  static CollisionEndpoint Entity(EntityId id);
  static CollisionEndpoint WorldGround();

  bool operator==(const CollisionEndpoint& other) const;
  bool operator<(const CollisionEndpoint& other) const;
};

struct ContactSnapshot
{
  CollisionEndpoint a;
  CollisionEndpoint b;
  
  cyclone::Vector3 point;
  cyclone::Vector3 normal;
  double closingSpeed = 0.0f;
};

struct CollisionPairState
{
  bool active = false;
  unsigned quietFrames = 0;
  unsigned missingFrames = 0;
  ContactSnapshot lastContact{};
};

struct CollisionPairKey
{
  CollisionEndpoint a;
  CollisionEndpoint b;
  
  static CollisionPairKey Make(
    CollisionEndpoint first,
    CollisionEndpoint second);
  
  bool operator<(const CollisionPairKey& other) const;
};