#pragma once

template<typename T, int Capacity>
template<typename U, typename... Args>
EntityId ObjectPool<T, Capacity>::Create(Args&&... args)
{
  for (int i = 0; i < Capacity; ++i)
  {
    if (!is_occupied_[i])
    {
      // Make new object
      T* object = new U(std::forward<Args>(args)...);
      objects_[i] = object;
      
      // Define `i` slot as occupied
      is_occupied_[i] = true;
      
      // Define a new EntityId
      EntityId id;
      id.slot = i;
      id.generation = generations_[i];
      
      return id;
    }
  }
    
  return EntityId();
}

template<typename T, int Capacity>
T* ObjectPool<T, Capacity>::Get(EntityId id)
{
  T* object = objects_[id.slot];
  if (id.generation == generations_[id.slot])
    return object;
  return nullptr;
}

template <typename T, int Capacity>
void ObjectPool<T, Capacity>::Destroy(EntityId id)
{
  if (!is_occupied_[id.slot])
    return;
    
  delete objects_[id.slot];
  is_occupied_[id.slot] = false;
  ++generations_[id.slot];
}

template <typename T, int Capacity>
void ObjectPool<T, Capacity>::Clear()
{
  for (int i = 0; i < Capacity; ++i)
  {
    if (is_occupied_[i])
    {
      EntityId id;
      id.slot = i;
      Destroy(id);
    }
  }
}
