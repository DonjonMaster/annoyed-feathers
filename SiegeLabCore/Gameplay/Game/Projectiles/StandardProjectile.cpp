#include "StandardProjectile.h"

void StandardProjectile::ConfigurePhysics()
{
  double mass = 1.0;
  double radius = 0.28;
  double inertia = 0.4 * mass * radius * radius;
  
  cyclone::Matrix3 inertiaTensor;
  inertiaTensor.setDiagonal(inertia, inertia, inertia);
  
  auto& body = GetBody();
  body.setMass(mass);
  body.setInertiaTensor(inertiaTensor);
  body.setDamping(0.99, 0.99);
  body.setCanSleep(true);
  body.setAwake(false);
  
  sphere_.radius = radius;
  sphere_.body = &body;
}
