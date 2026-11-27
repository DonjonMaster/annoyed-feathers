#pragma once
#include <map>
#include <vector>

#include "CollisionEvent.h"
#include "SiegeLabCore/PhysicsWorld/ContactSnapshot.h"

class CollisionEventGenerator
{
public:
  std::vector<CollisionEvent> Generate(
    const std::vector<ContactSnapshot>& snapshots,
    bool coverageComplete);
  
  void Reset();
  
  void RemoveEndpoint(CollisionEndpoint endpoint);
  
  
private:
  using StateMap = std::map<CollisionPairKey, CollisionPairState>;
  
  static CollisionEvent MakeEvent(
    CollisionEventType type,
    const CollisionPairState& state);
  
  StateMap states_;
};
