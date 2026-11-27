#pragma once
#include "Block.h"

class CubeBlock : public Block
{
public:
  CubeBlock(float _half_size, cyclone::Vector3 _pos);
  void ConfigurePhysics() override;
};
