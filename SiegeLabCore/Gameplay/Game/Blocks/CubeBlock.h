#pragma once
#include "Block.h"

class CubeBlock : public Block
{
public:
  void ConfigurePhysics() override;
};
