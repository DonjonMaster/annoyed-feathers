#pragma once

struct EntityId
{
  int slot = -1;
  int generation = -1;
  
  // Check if EntityId has been created successfully
  bool IsValid() const { return slot >= 0 && generation >= 0; }
};
