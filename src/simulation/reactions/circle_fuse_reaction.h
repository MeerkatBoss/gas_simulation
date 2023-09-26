/**
 * @file circle_fuse_reaction.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-26
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_REACTIONS_CIRCLE_FUSE_REACTION_H
#define __SIMULATION_REACTIONS_CIRCLE_FUSE_REACTION_H

#include "simulation/circle_molecule.h"
#include "simulation/reaction_builder.h"
#include "simulation/scene_object.h"
#include "simulation/square_molecule.h"

namespace sim
{

class CircleFuseReaction : public Reaction
{
public:
  CircleFuseReaction(MoleculeController& controller,
                     const math::Vec& position,
                     const math::Vec& velocity) :
    Reaction(controller),
    m_position(position),
    m_velocity(velocity),
    m_spawned(false)
  {
  }

  virtual bool hasNextResult() const override { return !m_spawned; }

  virtual void spawnNextResult() override;

private:
  math::Vec m_position;
  math::Vec m_velocity;
  bool m_spawned;
};

class CircleFuseReactionTemplate : public ReactionTemplate
{
public:
  CircleFuseReactionTemplate(MoleculeController& controller) :
    ReactionTemplate(controller)
  {
  }

  virtual Reaction* startReaction(const Reagents& reagents) override
  {
    using math::Vec;
    using math::Point;

    if (reagents.circles.getSize() == 2 &&
        reagents.squares.isEmpty())
    {
      const CircleMolecule* molecule0 = reagents.circles[0];
      const CircleMolecule* molecule1 = reagents.circles[1];

      const double m0 = molecule0->getMass();
      const double m1 = molecule1->getMass();

      const Vec v0 = molecule0->velocity();
      const Vec v1 = molecule1->velocity();

      const Point x0 = molecule0->transform().getPosition();
      const Point x1 = molecule1->transform().getPosition();

      if ((x1 - x0).isZero())
      {
        return nullptr;
      }

      // Molecules are flying away from each other
      if (Vec::dotProduct(v0, x1 - x0) < 0 &&
          Vec::dotProduct(v1, x0 - x1) < 0)
      {
        return nullptr;
      }

      Vec position = x1;
      Vec velocity = (m0 * v0 + m1 * v1) / (m0 + m1);

      return new CircleFuseReaction(m_controller, position, velocity);
    }

    return nullptr;
  }
};

} // namespace sim

#endif /* circle_fuse_reaction.h */
