#include "../SiegeLabCore/Gameplay/Game/Projectiles/HeavyProjectile.h"
#include "../SiegeLabCore/Gameplay/Game/Projectiles/StandardProjectile.h"
#include "../SiegeLabCore/Gameplay/Scene/ObjectPool.h"
#include "../SiegeLabCore/Gameplay/Scene/SceneObjects.h"
#include "gtest/gtest.h"

TEST(Pool, CapacityLimit)
{
  ObjectPool<int, 3> pool;
  
  EXPECT_TRUE(pool.Create(10).IsValid());
  EXPECT_TRUE(pool.Create(20).IsValid());
  EXPECT_TRUE(pool.Create(30).IsValid());
  
  // Pool is full
  EXPECT_FALSE(pool.Create(40).IsValid());
}

TEST(Pool, RecycledSlotChangesGeneration)
{
  ObjectPool<int, 1> pool;
  
  EntityId a_id = pool.Create(7);
  pool.Destroy(a_id);
  EntityId b_id = pool.Create(42);
  
  EXPECT_EQ(b_id.slot, 0);
  EXPECT_EQ(b_id.generation, 1);
}

TEST(Pool, StaleHandleRejected)
{
  ObjectPool<int, 1> pool;
  
  EntityId a_id = pool.Create(7);
  pool.Destroy(a_id);
  EntityId b_id = pool.Create(42);
  
  int* a = pool.Get(a_id);
  EXPECT_FALSE(a);
  
  int* b = pool.Get(b_id);
  EXPECT_TRUE(b);
  EXPECT_EQ(*b, 42);
}

TEST(Pool, LiveAddressStable)
{
  ObjectPool<int, 3> pool;
  
  EntityId a_id = pool.Create(10); 
  int* p = pool.Get(a_id);
  pool.Create(20);
  pool.Create(30);
  
  EXPECT_EQ(pool.Get(a_id), p);
  EXPECT_EQ(*p, 10);
}

TEST(Pool, ClearInvalidateHandles)
{
  ObjectPool<int, 2> pool;
  
  EntityId a_id = pool.Create(10);
  EntityId b_id = pool.Create(20);
  pool.Clear();
  EntityId c_id = pool.Create(30);
  
  EXPECT_EQ(pool.Get(a_id), nullptr);
  EXPECT_EQ(pool.Get(b_id), nullptr);
  EXPECT_EQ(*pool.Get(c_id), 30);
}

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

