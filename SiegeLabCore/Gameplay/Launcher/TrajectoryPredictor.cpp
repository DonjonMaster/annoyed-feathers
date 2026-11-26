#include "TrajectoryPredictor.h"

#include <iostream>
#include <raymath.h>

#include "SiegeLabCore/Gameplay/Game/Projectiles/HeavyProjectile.h"
#include "SiegeLabCore/Gameplay/Game/Projectiles/Projectile.h"
#include "SiegeLabCore/Gameplay/Game/Projectiles/StandardProjectile.h"

TrajectoryPrediction TrajectoryPredictor::PredictUntilFirstContact(
  const ShotSettings& _shot_settings)
{
  constexpr int MAX_STEPS = 64;
  constexpr float STEP_DURATION = 1.f / 60.f;
  
  // If last prediction is valid, return it, don't calculate another prediction
  if (CanGivePreviousPrediction(_shot_settings))
    return m_prediction;
  
  m_prediction.shot_settings = _shot_settings;
  m_prediction.positions.clear();
  m_prediction.end_with_collision = false;
  
  // Assign a projectile of the same kind for the `predictor_projectile`
  Projectile* predictor_projectile = MakePredictorProjectile(_shot_settings);
  cyclone::RigidBody& predictor_body = predictor_projectile->GetBody();
  
  for (int i = 0; i < MAX_STEPS; ++i)
  {
    predictor_body.addForce(cyclone::Vector3(0, -9.81, 0));
    predictor_body.integrate(STEP_DURATION);
    m_prediction.positions.emplace_back(predictor_body.getPosition());
    
    // TODO: Check if projectile is colliding with something, break when it does
  }
  
  delete predictor_projectile;
  return m_prediction;
}

bool TrajectoryPredictor::CanGivePreviousPrediction(
  const ShotSettings& _shot_settings) const
{
  return  m_prediction.shot_settings.kind == _shot_settings.kind ||
    m_prediction.shot_settings.speed == _shot_settings.speed;
    // TODO: Check if direction is same
}

Projectile* TrajectoryPredictor::MakePredictorProjectile(const ShotSettings& _shot_settings)
{
  Projectile* predictor_projectile = nullptr;
  
  switch (_shot_settings.kind)
  {
  case ProjectileKind::kStandard:
    predictor_projectile = new StandardProjectile(); break;
  case ProjectileKind::kHeavy:
    predictor_projectile = new HeavyProjectile(); break;
  }
  
  predictor_projectile->ConfigurePhysics();
  
  predictor_projectile->GetBody().setAwake(true);
  predictor_projectile->GetBody().setPosition(_shot_settings.origin);
  predictor_projectile->GetBody().setVelocity(
                    _shot_settings.direction * _shot_settings.speed);
  
  return predictor_projectile;
}
