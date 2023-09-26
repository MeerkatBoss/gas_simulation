/**
 * @file square_split_reaction.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-26
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_REACTIONS_SQUARE_SPLIT_REACTION_H
#define __SIMULATION_REACTIONS_SQUARE_SPLIT_REACTION_H

#include "simulation/circle_molecule.h"
#include "simulation/reaction_builder.h"
#include "simulation/scene_object.h"
#include "simulation/square_molecule.h"

namespace sim
{

class SquareSplitReaction : public Reaction
{
public:
  SquareSplitReaction(MoleculeController& controller,
                     const math::Vec& position,
                     const math::Vec& velocity,
                     double mass) :
    Reaction(controller),
    m_position(position),
    m_velocity(velocity),
    m_mass(mass),
    m_spawned(false)
  {
  }

  virtual bool hasNextResult() const override { return !m_spawned; }

  virtual void spawnNextResult() override;

private:
  math::Vec m_position;
  math::Vec m_velocity;
  double    m_mass;
  bool      m_spawned;
};

class SquareSplitReactionTemplate : public ReactionTemplate
{
public:
  SquareSplitReactionTemplate(MoleculeController& controller) :
    ReactionTemplate(controller)
  {
  }

  virtual Reaction* startReaction(const Reagents& reagents) override
  {
    if (reagents.circles.isEmpty() &&
        reagents.squares.getSize() == 2)
    {
      const SquareMolecule* m0 = reagents.squares[0];
      const SquareMolecule* m1 = reagents.squares[1];

      math::Vec position = m1->transform().getPosition();
      math::Vec velocity = (m0->getMass() * m0->velocity() + 
                            m1->getMass() * m1->velocity())
                            / (m0->getMass() + m1->getMass());

      return new SquareSplitReaction(
          m_controller,
          position,
          velocity,
          m0->getMass() + m1->getMass());
    }

    return nullptr;
  }
};

}
#endif /* square_split_reaction.h */
