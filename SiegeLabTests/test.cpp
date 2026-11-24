#include "../SiegeLabCore/Gameplay/Scene/ObjectPool.h"
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