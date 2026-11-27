#include "PillarBlock.h"

PillarBlock::PillarBlock(float _half_size, float _height, cyclone::Vector3 _pos)
  : Block(_pos)
{
  m_box_.halfSize = cyclone::Vector3(_half_size, _height, _half_size);
}

void PillarBlock::ConfigurePhysics()
{
  m_box_.body = &m_body_;
}
