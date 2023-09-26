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
    using math::Vec;
    using math::Point;

    if (reagents.circles.isEmpty() &&
        reagents.squares.getSize() == 2)
    {
      const SquareMolecule* molecule0 = reagents.squares[0];
      const SquareMolecule* molecule1 = reagents.squares[1];

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

      const double speed0 = v0.projectOn(x1 - x0).length();
      const double speed1 = v1.projectOn(x0 - x1).length();

      const double energy = (m0*speed0*speed0 + m1*speed1*speed1) / 2;

      // Not enough energy
      if (energy < 0.5*(m0 + m1))
      {
        return nullptr;
      }

      Vec position = (x0 + x1) / 2;
      Vec velocity = (m0 * v0 + m1 * v1) / (m0 + m1);

      return new SquareSplitReaction(m_controller, position, velocity, m0 + m1);
    }

    return nullptr;
  }
};

}
#endif /* square_split_reaction.h */
