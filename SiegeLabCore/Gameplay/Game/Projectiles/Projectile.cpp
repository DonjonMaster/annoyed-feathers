#include "Projectile.h"

Projectile::Projectile()
{
  sphere_.body = &GetBody();
  sphere_.offset = cyclone::Matrix4();
}

void Projectile::Fire(ShotSettings settings)
{
  // TODO : Define the new body_ parameters based on settings
}

void Projectile::RegisterPhysics(PhysicsWorld& world)
{
  world.RegisterSphere(id_, body_, sphere_);
}
