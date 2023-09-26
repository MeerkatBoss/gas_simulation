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
    if (reagents.circles.getSize() == 2 &&
        reagents.squares.isEmpty())
    {
      const CircleMolecule* m0 = reagents.circles[0];
      const CircleMolecule* m1 = reagents.circles[1];

      math::Vec position = (m0->transform().getPosition() +
                            m1->transform().getPosition()) / 2;

      math::Vec velocity = (m0->getMass() * m0->velocity() + 
                            m1->getMass() * m1->velocity())
                            / (m0->getMass() + m1->getMass());

      return new CircleFuseReaction(m_controller, position, velocity);
    }

    return nullptr;
  }
};

} // namespace sim

#endif /* circle_fuse_reaction.h */
