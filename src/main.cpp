/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include <SiegeLabCore/Gameplay/Camera/OrbitCamera.h>

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "SiegeLabCore/Gameplay/Camera/CameraManager.h"
#include "SiegeLabCore/Gameplay/Game/GameController.h"
#include "SiegeLabCore/Gameplay/Launcher/Launcher.h"
#include "SiegeLabCore/Gameplay/Launcher/TrajectoryPredictor.h"

int main()
{
  GameController game_controller;
  game_controller.Run();

  // Tell the window to use vsync and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

  // Create the window and OpenGL context
  InitWindow(800, 600, "Hello Raylib");

  // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
  SearchAndSetResourceDir("resources");

  // Load a texture from the resources directory
  Texture wabbit = LoadTexture("wabbit_alpha.png");

  Launcher launcher;
  ShotSettings shot_settings = launcher.GetShotSettings();
  TrajectoryPredictor trajectory_predictor;
  TrajectoryPrediction prediction = trajectory_predictor.PredictUntilFirstContact(shot_settings);
  
  CameraManager camera_manager;
  OrbitCamera camera;
  
  camera.target = {2, 1, 1};
  
  camera_manager.SetActive(&camera);
  
  InputController input_controller;
  
  // game loop
  while (!WindowShouldClose())
  // run the loop until the user presses ESCAPE or presses the Close button on the window
  {
    float dt = GetFrameTime();
    InputSnapshot inputs = input_controller.capture();
    
    camera_manager.GetCamera().Update(inputs, dt);
    
    // drawing
    BeginDrawing();

    // Setup the back buffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);
    
    BeginMode3D(camera);

    // draw some text using the default font
    DrawText("Hello Raylib", 200, 200, 20,WHITE);

    // draw our texture to the screen
    DrawTexture(wabbit, 400, 200, WHITE);
    
    DrawCube({2, 1, 1}, 2, 2, 2, WHITE);

    for (int i = 0; i < prediction.positions.size() - 1; ++i)
    {
      cyclone::Vector3 a = prediction.positions[i];
      cyclone::Vector3 b = prediction.positions[i + 1];
      Vector3 c(a.x, a.y, a.z);
      Vector3 d(b.x, b.y, b.z);
      DrawLine3D(c, d, RED);
    }
    
    EndMode3D();
    
    // end the frame and get ready for the next one  (display frame, poll input, etc...)
    EndDrawing();
  }

  // cleanup
  // unload our texture so it can be cleaned up
  UnloadTexture(wabbit);

  // destroy the window and cleanup the OpenGL context
  CloseWindow();
  return 0;
}
