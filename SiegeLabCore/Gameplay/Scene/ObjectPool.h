#pragma once
#include <cstdint>
#include <vector>

#include "EntityId.h"

template <typename T, int Capacity>
class ObjectPool
{
public:
  ObjectPool() : m_objects(Capacity), m_is_occupied(Capacity),
                 m_generations(Capacity)
  {
  }

  // Create an object inside the object pool, fails if object pool is full
  template <typename U = T, typename... Args>
  EntityId Create(Args&&... args);

  // Get an object from requested ID
  T* Get(EntityId id);

  // Destroy an object from requested ID
  void Destroy(EntityId id);

  // Clear all objects in pool
  void Clear();

private:
  std::vector<T*> m_objects;

  // Define if a value is occupied or not. Managed by Create and RequestDelete
  std::vector<bool> m_is_occupied;

  // Generations are incremented independently of the id of the objects.
  // If the generation's id is different from the object's id,
  // Then, slot is freed
  std::vector<uint8_t> m_generations;
};

#include "ObjectPool.inl"
