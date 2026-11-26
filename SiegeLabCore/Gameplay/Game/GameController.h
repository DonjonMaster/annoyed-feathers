#pragma once

class GameController
{
public:
  void Run();

private:
  void Init();
  void Destroy();
  void ProcessInput();
  void FixedTick(float dt);
  void Restart();
};
