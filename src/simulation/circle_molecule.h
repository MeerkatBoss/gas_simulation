/**
 * @file circle_molecule.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_CIRCLE_MOLECULE_H
#define __SIMULATION_CIRCLE_MOLECULE_H

#include "simulation/molecule.h"

namespace sim
{

class CircleMolecule : public Molecule
{
public:
  CircleMolecule(const math::Vec&       velocity  = math::Vec(),
                 const math::Transform& transform = math::Transform()) :
    Molecule(1, velocity, transform)
  {
  }

  void addToReaction(ReactionBuilder& builder) const override;

  BoundingBox getBoundingBox() const override;

  void draw(ui::Canvas& window,
            const math::Transform& parent_transform) const override;

  ~CircleMolecule() override = default;
};

} // namespace sim

#endif /* circle_molecule.h */
