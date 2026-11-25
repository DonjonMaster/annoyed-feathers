#include <raylib.h>
#include <raymath.h>
#include <gtest/gtest.h>

#include "SiegeLabCore/Gameplay/Camera/OrbitCamera.h"
#include "SiegeLabCore/Gameplay/Launcher/Launcher.h"
#include "SiegeLabCore/Gameplay/Launcher/ShotSettings.h"

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

TEST(Launcher, ZeroAzimuthHasNoZComponent)
{
  Launcher launcher;
  launcher.SetYaw(0.f);
  launcher.SetPitch(30.f);
  
  ShotSettings shot_settings = launcher.GetShotSettings();
  ExpectVectorNear(shot_settings.direction, { 0.8660f, 0.5f, 0.0f }, 1e-3f);
  EXPECT_NEAR(shot_settings.direction.z, 0.f, 1e-3f);
}

TEST(Launcher, DirectionIsNormalized)
{
  Launcher launcher;
  
  launcher.SetYaw(30.f);
  launcher.SetPitch(30.f);
  EXPECT_NEAR(Vector3Length(launcher.GetShotSettings().direction), 1.f, 1e-4f);
  
  launcher.SetYaw(-30.f);
  launcher.SetPitch(45.f);
  EXPECT_NEAR(Vector3Length(launcher.GetShotSettings().direction), 1.f, 1e-4f);
}

TEST(Launcher, ParametersAreClamped)
{
  Launcher launcher;
  launcher.SetYaw(45.f);
  launcher.SetPitch(-10.f);
  launcher.SetSpeed(30);
  
  EXPECT_EQ(launcher.GetYaw(), 30.f);
  EXPECT_EQ(launcher.GetPitch(), 5.f);
  EXPECT_EQ(launcher.GetSpeed(), 22);
}

TEST(Launcher, AimIsIndependantFromCamera)
{
  Launcher launcher;
  OrbitCamera camera;
  
  launcher.SetYaw(20.f);
  launcher.SetPitch(30.f);
  
  camera.yaw = 0.f;
  ExpectVectorNear(launcher.GetShotSettings().direction, { 0.8138f, 0.5f, 0.2962f }, 1e-3f);
  
  camera.yaw = 120.f;
  ExpectVectorNear(launcher.GetShotSettings().direction, { 0.8138f, 0.5f, 0.2962f }, 1e-3f);
}

TEST(Launcher, SelectsConcreteProjectileKind)
{
  InputSnapshot input;
  
  Launcher launcher;
  launcher.SetSpeed(16);
  
  launcher.Aim(input);
  launcher.GetShotSettings();
  
  launcher.Aim(input);
  launcher.GetShotSettings();
}