#pragma once
#include <vector>

#include "ShotSettings.h"

struct TrajectoryPrediction
{
  std::vector<Vector3> positions;
  bool end_with_collision;
};

class TrajectoryPredictor
{
public:
  TrajectoryPrediction PredictUntilFirstContact(const ShotSettings& _shot_settings);
  
private:
  bool IsPredictionValid();
  TrajectoryPrediction m_prediction;
};
