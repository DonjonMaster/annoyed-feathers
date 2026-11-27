#include "GameController.h"

#include <raylib.h>

#include "Blocks/CubeBlock.h"
#include "SiegeLabCore/Gameplay/Camera/CameraManager.h"
#include "SiegeLabCore/Gameplay/Camera/OrbitCamera.h"

GameController* GameController::m_instance = nullptr;

void GameController::Run()
{
  Init();

  while (!WindowShouldClose())
  {
    const float dt = GetFrameTime();
    ProcessInput();
    FixedTick(dt);
  }

  Destroy();
}

void GameController::Init()
{
  m_camera_manager.SetActive(&m_orbit_camera);
}

void GameController::Destroy()
{
}

void GameController::ProcessInput()
{
  m_input_snapshot = m_input_controller.Capture();
}

void GameController::FixedTick(const float _dt)
{
  m_scene_objects.GetPhysicsWorld().Step(_dt);
  m_orbit_camera.Update(m_input_snapshot, _dt);
  
  m_launcher.Aim(m_input_snapshot);
  m_shot_settings = m_launcher.GetShotSettings();
  
  BeginDrawing();
  
  ClearBackground(Color(105, 206, 235));
  
  BeginMode3D(m_orbit_camera);
  
  DrawGrid(60, 1.f);
  
  // Draw all game entities in the scene
  for (auto& game_entity : m_scene_objects.GetGameEntities())
  {
    if (!game_entity)
      break;
    game_entity->Draw();
  }
  
  // Draw launcher with its shot settings
  const cyclone::Vector3 o = m_shot_settings.origin;
  const cyclone::Vector3 s = o - (m_shot_settings.direction * 0.5f);
  const cyclone::Vector3 e = o + (m_shot_settings.direction * 1.25f);
  
  DrawCylinder(Vector3(o.x, o.y, o.z),
    0.75f, 0.75f, 0.05f, 24, BLACK);
  
  DrawCylinder(Vector3(o.x, o.y + 0.05f, o.z),
    0.15f, 0.15f, 0.75f, 24, DARKGRAY);
  
  DrawCylinderEx(Vector3(s.x, s.y + 0.65f, s.z), Vector3(e.x, e.y + 0.65f, e.z),
    0.35f, 0.4f, 24, BLACK);
  
  EndMode3D();
  
  EndDrawing();
}

void GameController::Restart()
{
}
