#pragma once
#include <vector>

#include "ICollisionListener.h"

class CollisionEventDispatcher
{
public:
  // Equivalent of the id system
  using Token = std::uint64_t;
  
  Token Subscribe(ICollisionListener& listener);
  bool Unsubscribe(Token token);
  
  void Publish(const std::vector<CollisionEvent>& events);
  
private:
  struct Entry
  {
    Token token;
    ICollisionListener* listener;
    bool active;
  };
  
  Entry* FindActive(Token token);
  
  // Erase listeners if no longer active
  void Compact();
  
  // List of all subscribed entities
  std::vector<Entry> listeners_;
  Token nextToken_ = 1;
  unsigned dispatchDepth_ = 0;
};
