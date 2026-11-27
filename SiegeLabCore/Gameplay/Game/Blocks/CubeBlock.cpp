#include "CubeBlock.h"

void CubeBlock::ConfigurePhysics()
{
  box_.halfSize = cyclone::Vector3(0.5, 10.0, 0.5);
  box_.body = &body_;
}
