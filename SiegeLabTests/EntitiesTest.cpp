#include <gtest/gtest.h>

#include "SiegeLabCore/Gameplay/Game/Projectiles/HeavyProjectile.h"
#include "SiegeLabCore/Gameplay/Game/Projectiles/StandardProjectile.h"
#include "SiegeLabCore/Gameplay/Scene/SceneObjects.h"

TEST(Entities, FactoryCreatesDerivedTypes)
{
  SceneObjects scene_objects;
  
  EntityId standard_id = scene_objects.CreateEntity<StandardProjectile>();
  EntityId heavy_id = scene_objects.CreateEntity<HeavyProjectile>();
  
  EXPECT_TRUE(standard_id.IsValid());
  EXPECT_TRUE(heavy_id.IsValid());
  EXPECT_TRUE(scene_objects.Get(standard_id) != nullptr);
  EXPECT_TRUE(scene_objects.Get(heavy_id) != nullptr);
}

TEST(Entities, VirtualDrawDispatchWithoutRTTI)
{
  
}

TEST(Entities, ProjectilesProfilesAreDistinct)
{
}

TEST(Entities, PillarCubeAndCageProfiles)
{
}

TEST(Entites, StableColliderAddressAndSafeRemoval)
{}

TEST(Entites, ConstrainedFactoryRejectsUnrelatedTypes)
{}

