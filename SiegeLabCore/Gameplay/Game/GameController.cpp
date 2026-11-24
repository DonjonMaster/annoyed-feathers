#include "GameController.h"

#include "build/external/raylib-master/src/raylib.h"


void GameController::Run()
{
  Init();

  while (!WindowShouldClose())
  {
    const double dt = GetFrameTime();
    ProcessInput();
    FixedTick(dt);
  }

  Destroy();
}

void GameController::Init()
{
}

void GameController::Destroy()
{
}

void GameController::ProcessInput()
{
}

void GameController::FixedTick(const double dt)
{
}

void GameController::Restart()
{
}
