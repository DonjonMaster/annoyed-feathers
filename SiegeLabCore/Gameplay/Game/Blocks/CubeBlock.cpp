#include "CubeBlock.h"

CubeBlock::CubeBlock(float _half_size, cyclone::Vector3 _pos)
  : Block(_pos)
{
  m_box_.halfSize = cyclone::Vector3(_half_size, _half_size, _half_size);
}

void CubeBlock::ConfigurePhysics()
{
  m_box_.body = &m_body_;
}
