#pragma once
#include "Block.h"

class CageBlock : Block
{
public:
  void ConfigurePhysics() override;
  void Draw() override;

  // Threshold of damage caused by hit for cage to be destroyed
  cyclone::real m_break_threshold;
};
