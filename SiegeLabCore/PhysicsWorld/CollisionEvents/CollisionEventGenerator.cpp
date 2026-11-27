#include "CollisionEventGenerator.h"

#include <set>

namespace
{
  float kEnterSpeed = 1.0f;
  float kQuietSpeed = 0.2f;
  unsigned kQuietFramesToExit = 3;
  unsigned kMissingFramesToExit = 2;
}

std::vector<CollisionEvent> CollisionEventGenerator::Generate(
  const std::vector<ContactSnapshot>& snapshots, bool coverageComplete)
{
  std::vector<CollisionEvent> events;
  
  std::map<CollisionPairKey, ContactSnapshot> contactsByPair;
  
  // Link snapshots into pairs
  for (const ContactSnapshot& original : snapshots)
  {
    ContactSnapshot snapshot = original;
    
    // Makes sure the IDs and normal are consistent with the pair key
    if (snapshot.b < snapshot.a)
    {
      std::swap(snapshot.a, snapshot.b);
      snapshot.normal *= -1.0f;
    }
    
    const CollisionPairKey key = CollisionPairKey::Make
    (snapshot.a, snapshot.b);
    
    auto found = contactsByPair.find(key);
    
    if (found == contactsByPair.end() ||
      snapshot.closingSpeed > found->second.closingSpeed)
    {
      contactsByPair[key] = snapshot;
    }
  }
  
  std::set<CollisionPairKey> seenPairs;
  
  // Check every contact snapshots
  for (auto& [key, snapshot] : contactsByPair)
  {
    seenPairs.insert(key);
    CollisionPairState& state = states_[key];
    // Add snapshot data to the current state of collision
    state.lastContact = snapshot;
    state.missingFrames = 0;
    
    // Check if collision is already active or not
    if (!state.active)
    {
      // If it is not, check if it can be activated
      if (snapshot.closingSpeed >= kEnterSpeed)
      {
        state.active = true;
        state.quietFrames = 0;
        events.push_back(MakeEvent(CollisionEventType::Enter, state));
      }
      continue;
    }
    // Check if collision is still happening
    if (snapshot.closingSpeed <= kQuietSpeed)
    {
      ++state.quietFrames;
      // Check if collision can be exited
      if (state.quietFrames >= kQuietFramesToExit)
      {
        events.push_back(MakeEvent(CollisionEventType::Exit, state));
        state.active = false;
        state.quietFrames = 0;
        state.missingFrames = 0;
      }
    }
    else
    {
      // Interrupts quiet contact, due to speed exceeding reality
      state.quietFrames = 0;
    }
  }
  // Every pair were covered
  if (coverageComplete)
  {
    for (auto& [key, state] : states_)
    {
      if (!state.active || seenPairs.contains(key))
        continue;
      
      ++state.missingFrames;
      state.quietFrames = 0;
      // If a pair is still in collision, interrupts it
      if (state.missingFrames >= kMissingFramesToExit)
      {
        events.push_back(MakeEvent(CollisionEventType::Exit, state));
        state.active = false;
        state.quietFrames = 0;
        state.missingFrames = 0;
      }
    }
  }
  return events;
}

void CollisionEventGenerator::Reset()
{
  states_.clear();
}

void CollisionEventGenerator::RemoveEndpoint(CollisionEndpoint endpoint)
{
  for (std::map<CollisionPairKey, CollisionPairState>::iterator 
    it = states_.begin(); it != states_.end();)
  {
    if (it->first.a == endpoint || it->first.b == endpoint)
      it = states_.erase(it);
    else
      ++it;
  }
}

CollisionEvent CollisionEventGenerator::MakeEvent(CollisionEventType type,
  const CollisionPairState& state)
{
  return {
    type,
    state.lastContact.a.entity,
    state.lastContact.b.entity,
    state.lastContact.point,
    state.lastContact.normal,
    state.lastContact.closingSpeed
  };
}
