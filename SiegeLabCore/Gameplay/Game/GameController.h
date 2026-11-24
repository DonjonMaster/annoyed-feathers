#pragma once

class GameController
{
public:
    void Run();
    
private:
    void Init();
    void Destroy();
    void ProcessInput();
    void FixedTick(const float dt);
    void Restart();
};
