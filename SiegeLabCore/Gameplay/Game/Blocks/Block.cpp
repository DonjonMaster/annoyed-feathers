#include "Block.h"

#include <raylib.h>

Block::Block(cyclone::Vector3 _pos)
{
  body_.setPosition(_pos);
}

void Block::RegisterPhysics(PhysicsWorld& world)
{
  world.RegisterBox(id_, body_, box_);
}

void Block::Draw()
{
  const cyclone::Vector3 p = body_.getPosition();
  const cyclone::Vector3 s = box_.halfSize;
  DrawCube(Vector3(p.x, p.y, p.z), s.x, s.y, s.z, WHITE);
}
