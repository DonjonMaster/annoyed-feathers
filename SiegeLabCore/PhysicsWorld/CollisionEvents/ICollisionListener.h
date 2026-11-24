#pragma once

class ICollisionListener
{
public:
  template <typename Events>
  void OnCollision(Events);
};
