#include "CollisionEventDispatcher.h"

#include <algorithm>

CollisionEventDispatcher::Token 
CollisionEventDispatcher::Subscribe(ICollisionListener& listener)
{
  const Token token = nextToken_++;
  listeners_.push_back({token, &listener, true});
  return token;
}

bool CollisionEventDispatcher::Unsubscribe(Token token)
{
  // Check if listener is subscribed
  Entry* entry = FindActive(token);
  if (!entry)
    return false;
  
  entry->active = false;
  
  // no more listeners
  if (dispatchDepth_ == 0)
    Compact();
  
  return true;
}

void CollisionEventDispatcher::Publish(
  const std::vector<CollisionEvent>& events)
{
  // Only subscribed listeners will be notified
  std::vector<Token> tokens;
  tokens.reserve(listeners_.size());
  
  for (const Entry& entry : listeners_)
  {
    if (entry.active)
      tokens.push_back(entry.token);
  }
  
  ++dispatchDepth_;

  try
  {
    // Check if someone unsubscribe during dispatching of events
    for (const CollisionEvent& event : events)
    {
      for (Token token : tokens)
      {
        Entry* entry = FindActive(token);
        if (entry)
          entry->listener->OnCollision(event);
      }
    }
  }
  // If he did, remove him from the dispatch
  catch (...)
  {
    --dispatchDepth_;
    if (dispatchDepth_ == 0)
      Compact();
    throw;
  }
  
  --dispatchDepth_;
  if (dispatchDepth_ == 0)
    Compact();
}

CollisionEventDispatcher::Entry* CollisionEventDispatcher::FindActive(
  Token token)
{
  for (Entry& entry : listeners_)
  {
    if (entry.token == token && entry.active)
      return &entry;
  }
  
  return nullptr;
}

void CollisionEventDispatcher::Compact()
{
  std::erase_if(
    listeners_, [](const Entry& entry) {return !entry.active; });
}
