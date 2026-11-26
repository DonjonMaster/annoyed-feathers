#pragma once
#include <optional>
#include <vector>

#include "ShotSettings.h"
#include "SiegeLabCore/Gameplay/Game/Projectiles/Projectile.h"

struct TrajectoryPrediction
{
  ShotSettings shot_settings;
  std::vector<cyclone::Vector3> positions;
  bool end_with_collision = false;
};

class TrajectoryPredictor
{
public:
  TrajectoryPrediction PredictUntilFirstContact(const ShotSettings& _shot_settings);
  
private:
  bool CanGivePreviousPrediction(const ShotSettings& _shot_settings) const;
  Projectile* MakePredictorProjectile(const ShotSettings& _shot_settings);
  
  TrajectoryPrediction m_prediction;
};
