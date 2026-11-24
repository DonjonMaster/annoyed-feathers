#pragma once
#include "Cyclone/include/collide_fine.h"

class PhysicsWorld
{
private:
    void RegisterSphere(int id, cyclone::RigidBody& body, 
        cyclone::CollisionSphere& sphere);
    void RegisterBox(int id, cyclone::RigidBody& body, 
        cyclone::CollisionBox& box);
    void RegisterPlane(cyclone::CollisionPlane plane);
    void UnregisterObject(int id);
    void Step (const float dt);
    void Reset();
};
