#pragma once
#include "Block.h"

class CubeBlock : public Block
{
public:
  CubeBlock(cyclone::Vector3 _pos) : Block(_pos) {}
  void ConfigurePhysics() override;
};
