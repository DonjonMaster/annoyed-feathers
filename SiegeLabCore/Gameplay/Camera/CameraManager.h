#pragma once
#include "ICameraController.h"
#include "SiegeLabCore/Gameplay/Game/GameController.h"

class CameraManager
{
public:
  void SetActive(ICameraController *controller)
  {
    controller_ = controller;
  }
  ICameraController& GetCamera()
  {
    return *controller_;
  }
private:
  ICameraController* controller_;
};
