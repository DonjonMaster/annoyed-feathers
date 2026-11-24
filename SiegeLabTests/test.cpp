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
  
  int object_a = 7;
  int object_b = 42;
}