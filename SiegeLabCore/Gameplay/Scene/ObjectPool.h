#pragma once
#include <vector>

#include "EntityId.h"

template<typename T, int Capacity>
class ObjectPool
{
public:
  ObjectPool() : objects_(Capacity), is_occupied_(Capacity), generations_(Capacity) {}
  
  // Create an object inside the object pool, fails if object pool is full
  template<typename... Args>
  EntityId Create(Args... args);
  
  // Get an object from requested ID
  T* Get(EntityId id);
  
  // Destroy an object from requested ID
  void Destroy(EntityId id);

private:
  std::vector<T*> objects_;
  
  // Define if a value is occupied or not. Managed by Create and RequestDelete
  std::vector<bool> is_occupied_; 
  
  // Generations are incremented independently of the id of the objects.
  // If the generation's id is different from the object's id,
  // Then, slot is freed
  std::vector<uint8_t> generations_;
};

#include "ObjectPool.inl"