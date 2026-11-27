#pragma once
#include "ICameraController.h"

class CameraManager
{
public:
  // Set a camera controller as the active camera of the manager
  void SetActive(ICameraController *_controller)
  {
    m_controller = _controller;
  }
  
  // Get active camera controller of the manager
  ICameraController& GetCamera() const
  {
    return *m_controller;
  }
  
private:
  ICameraController* m_controller = nullptr;
};
