#include "Block.h"

#include <raylib.h>

Block::Block(const cyclone::Vector3& _pos)
{
  m_body_.setPosition(_pos);
}

void Block::RegisterPhysics(PhysicsWorld& _world)
{
  _world.RegisterBox(m_id_, m_body_, m_box_);
}

void Block::Draw()
{
  const cyclone::Vector3 p = m_body_.getPosition();
  const cyclone::Vector3 s = m_box_.halfSize;
  DrawCube(Vector3(p.x, p.y, p.z), s.x, s.y, s.z, WHITE);
}
