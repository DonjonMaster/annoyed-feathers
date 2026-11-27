#pragma once
#include "SiegeLabCore/Gameplay/Camera/CameraManager.h"
#include "SiegeLabCore/Gameplay/Camera/OrbitCamera.h"
#include "SiegeLabCore/Gameplay/Launcher/Launcher.h"
#include "SiegeLabCore/Gameplay/Scene/SceneObjects.h"

class GameController
{
public:
  void Run();

  // Get the controller instance of the game
  static GameController* GetInstance()
  {
    if (!m_instance)
      m_instance = new GameController;
    return m_instance;
  }
  
  // Get PhysicsWorld instance of the game
  PhysicsWorld& GetPhysicsWorld()
  {
    return m_scene_objects.GetPhysicsWorld();
  }
  
private:
  void Init();
  void Destroy();
  void ProcessInput();
  void FixedTick(float _dt);
  void Restart();
  
  // Static instance of the game controller
  static GameController* m_instance;
  
  // Contains all objects of the scene
  SceneObjects m_scene_objects;
  
  // Manage player's inputs
  InputController m_input_controller;
  InputSnapshot m_input_snapshot;
  
  // Handle player's camera
  CameraManager m_camera_manager;
  OrbitCamera m_orbit_camera;
  
  // Launcher goes pew!
  Launcher m_launcher;
  ShotSettings m_shot_settings;
};
