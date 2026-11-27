#include "raylib.h"
#include "resource_dir.h"

#include "SiegeLabCore/Gameplay/Game/GameController.h"

int main()
{
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(1600, 900, "Annoyed Feathers");
  SearchAndSetResourceDir("resources");
  
  GameController game_controller;
  game_controller.Run();
  
  CloseWindow();
  return 0;
}
