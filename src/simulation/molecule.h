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
#include "ui/render_window.h"

namespace sim
{

// Forward declaration
class ReactionBuilder;

// Forward declaration
class IntersectionBuilder;

class Molecule
{
public:
  Molecule(      double           mass      = 1,
           const math::Vec&       velocity  = math::Vec(),
           const math::Transform& transform = math::Transform()) :
    m_transform(transform),
    m_velocity(velocity),
    m_mass(mass)
  {
  }

  const math::Transform& transform() const { return m_transform; }
        math::Transform& transform()       { return m_transform; }

  const math::Vec& velocity() const { return m_velocity; }
        math::Vec& velocity()       { return m_velocity; }

  double getMass() const { return m_mass; };

  virtual void addToReaction(ReactionBuilder& builder) const = 0;

  virtual void addToIntersection(IntersectionBuilder& builder) const = 0;

  virtual void draw(ui::RenderWindow& window) const = 0;

  virtual ~Molecule() = default;

private:
  math::Transform m_transform;
  math::Vec       m_velocity;
  const double    m_mass;
};

} // namespace sim

#endif /* molecule.h */
