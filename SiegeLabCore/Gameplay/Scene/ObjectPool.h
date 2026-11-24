#pragma once
#include "EntityId.h"

template<typename T, int Capacity>
class ObjectPool
{
public:
  void Create();
  EntityId Get(int id);
  void Destroy(int id);
  void Clear();
  
private:
  int capacity = Capacity;
};
