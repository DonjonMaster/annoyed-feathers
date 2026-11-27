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
  m_scene_objects.CreateEntity<CubeBlock>(
    1.f,
    cyclone::Vector3(4, 0, 0)
  );
  
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
  
  BeginDrawing();
  
  ClearBackground(Color(105, 206, 235));
  
  BeginMode3D(m_orbit_camera);
  
  for (auto& game_entity : m_scene_objects.GetGameEntities())
  {
    if (!game_entity)
      break;
    game_entity->Draw();
  }
  
  EndMode3D();
  
  EndDrawing();
}

void GameController::Restart()
{
}
