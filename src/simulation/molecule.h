/**
 * @file molecule.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief
 *
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_MOLECULE_H
#define __SIMULATION_MOLECULE_H

#include "math/transform.h"
#include "simulation/scene_object.h"
#include "simulation/movable.h"

namespace sim
{

// Forward declaration
class ReactionBuilder;

class Molecule : public SceneObject, public Movable
{
public:
  Molecule(      double           mass      = 1,
           const math::Vec&       velocity  = math::Vec(),
           const math::Transform& transform = math::Transform()) :
    SceneObject(transform), Movable(mass, velocity)
  {
  }

  virtual bool isMovable() const override { return true; }

  virtual Movable* asMovable() override { return this; }

  virtual bool isTickable() const override { return true; }

  virtual void updateTick(double delta_time_seconds) override
  {
    transform().move(velocity() * delta_time_seconds);
  }

  virtual void addToReaction(ReactionBuilder& builder) const = 0;

  virtual void collide(SceneObject& other) const override;

  virtual ~Molecule() = default;
};

} // namespace sim

#endif /* molecule.h */
