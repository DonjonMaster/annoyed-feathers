#include "gtest/gtest.h"
#include "SiegeLabCore/Gameplay/Camera/OrbitCamera.h"

namespace
{
  void ExpectVectorNear(Vector3 actual, Vector3 expected, float tolerance)
  {
    EXPECT_NEAR(actual.x, expected.x, tolerance);
    EXPECT_NEAR(actual.y, expected.y, tolerance);
    EXPECT_NEAR(actual.z, expected.z, tolerance);
  }

  float Distance(Vector3 a, Vector3 b)
  {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    const float dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }
}

TEST(TestCaseName, TestName)
{
  EXPECT_EQ(2+3, 5);
  EXPECT_TRUE(true);
}

TEST(Camera, TargetAndRadiusRemainStable)
{
  OrbitCamera camera;
  InputSnapshot noInput{};
  
  camera.target = {2.0f, 1.0f, 0.0f};
  camera.radius = 10.0f;
  camera.yaw = 0.0f;
  camera.pitch = 20.0f;
  
  camera.Update(noInput, 0);
  const Vector3 initialPosition = camera.Position();
  
  ExpectVectorNear(initialPosition, {2.0f, 4.4202f, 9.3969f}, 1e-3f);
  ExpectVectorNear(camera.target, {2.0f, 1.0f, 0.0f}, 1e-3f);
  EXPECT_NEAR(Distance(initialPosition, camera.target), 10.0f, 1e-3f);
  
  camera.yaw = 90.0f;
  camera.pitch = 30.0f;

  camera.Update(noInput, 0.0f);
  const Vector3 finalPosition = camera.Position();

  ExpectVectorNear(finalPosition, {10.6603f, 6.0f, 0.0f}, 1e-3f);
  ExpectVectorNear(camera.target, {2.0f, 1.0f, 0.0f}, 1e-3f);
  EXPECT_NEAR(Distance(finalPosition, camera.target), 10.0f, 1e-3f);
}

TEST(Camera, PitchAndZoomAreClamped)
{
}


TEST(Camera, FullTurnReturnsToSamePose)
{
  OrbitCamera camera;
  InputSnapshot noInput{};
  
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.radius = 10.0f;
  camera.pitch = 20.0f;
  camera.yaw = 30.0f;
  
  camera.Update(noInput, 0.0f);
  const Vector3 before = camera.Position();

  camera.yaw = 390.0f;
  camera.Update(noInput, 0.0f);
  const Vector3 after = camera.Position();

  ExpectVectorNear(before, {4.6985f, 3.4202f, 8.1380f}, 1e-3f);
  EXPECT_NEAR(Distance(before, after), 0.0f, 1e-4f);
}

