#pragma once

template<typename T, int Capacity>
template<typename U, typename... Args>
EntityId ObjectPool<T, Capacity>::Create(Args&&... args)
{
  for (int i = 0; i < Capacity; ++i)
  {
    if (!m_is_occupied[i])
    {
      // Make new object
      T* object = new U(std::forward<Args>(args)...);
      m_objects[i] = object;
      
      // Define `i` slot as occupied
      m_is_occupied[i] = true;
      
      // Define a new EntityId
      EntityId id;
      id.slot = i;
      id.generation = m_generations[i];
      
      return id;
    }
  }
    
  return EntityId();
}

template<typename T, int Capacity>
T* ObjectPool<T, Capacity>::Get(EntityId id)
{
  T* object = m_objects[id.slot];
  if (id.generation == m_generations[id.slot])
    return object;
  return nullptr;
}

template <typename T, int Capacity>
void ObjectPool<T, Capacity>::Destroy(EntityId id)
{
  if (!m_is_occupied[id.slot])
    return;
    
  delete m_objects[id.slot];
  m_is_occupied[id.slot] = false;
  ++m_generations[id.slot];
}

template <typename T, int Capacity>
void ObjectPool<T, Capacity>::Clear()
{
  for (int i = 0; i < Capacity; ++i)
  {
    if (m_is_occupied[i])
    {
      EntityId id;
      id.slot = i;
      Destroy(id);
    }
  }
}
