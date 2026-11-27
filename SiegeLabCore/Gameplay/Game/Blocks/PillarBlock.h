#pragma once
#include "Block.h"

class PillarBlock : Block
{
public:
  PillarBlock(float _half_size, float _height, cyclone::Vector3 _pos);
  void ConfigurePhysics() override;
};
