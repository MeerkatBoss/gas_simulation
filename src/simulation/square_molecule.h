/**
 * @file square_molecule.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_SQUARE_MOLECULE_H
#define __SIMULATION_SQUARE_MOLECULE_H

#include <SFML/Graphics/Texture.hpp>
#include "math/transform.h"
#include "simulation/molecule.h"

namespace sim
{

class SquareMolecule : public Molecule
{
public:
  SquareMolecule(const sf::Texture&     texture,
                       double           mass      = 2,
                 const math::Vec&       velocity  = math::Vec(),
                 const math::Transform& transform = math::Transform()) :
    Molecule(texture, mass, velocity, transform)
  {
  }

  void addToReaction(ReactionBuilder& builder) const override;

  BoundingBox getBoundingBox() const override;

  ~SquareMolecule() override = default;
};

} // namespace sim

#endif /* square_molecule.h */
