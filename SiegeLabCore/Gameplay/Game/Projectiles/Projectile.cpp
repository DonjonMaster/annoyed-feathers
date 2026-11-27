#include "Projectile.h"

Projectile::Projectile()
{
  sphere_.body = &GetBody();
  sphere_.offset = cyclone::Matrix4();
}

void Projectile::Fire(ShotSettings _settings)
{
  // TODO : Define the new body parameters based on settings
}

void Projectile::RegisterPhysics(PhysicsWorld& _world)
{
  _world.RegisterSphere(m_id_, m_body_, sphere_);
}
