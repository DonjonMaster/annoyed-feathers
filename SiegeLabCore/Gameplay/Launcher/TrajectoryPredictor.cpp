#include "TrajectoryPredictor.h"

#include "SiegeLabCore/Gameplay/Game/Projectiles/Projectile.h"

TrajectoryPrediction TrajectoryPredictor::PredictUntilFirstContact(
  const ShotSettings& _shot_settings)
{
  constexpr int MAX_STEPS = 64;
  constexpr float STEP_DURATION = 1 / 60.f;
  
  // If last prediction is valid, return it, don't calculate another prediction
  if (IsPredictionValid())
    return m_prediction;
  
  // Assign a projectile of the same kind for the `predictor_projectile`
  // PredictionBody prediction_body = MakePredictionBody(_shot_settings);
  
  // Clear previous predictions and do steps and until projectile hits something
  m_prediction.positions.clear();
  m_prediction.end_with_collision = false;
  
  for (int i = 0; i < MAX_STEPS; ++i)
  {
  }
  
  return m_prediction;
}
