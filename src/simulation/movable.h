/**
 * @file movable.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_MOVABLE_H
#define __SIMULATION_MOVABLE_H

#include "math/vec.h"

namespace sim
{

class Movable
{
public:
  Movable(double mass, const math::Vec& velocity) :
    m_mass(mass), m_velocity(velocity)
  {
  }

  const math::Vec& velocity() const { return m_velocity; }
        math::Vec& velocity()       { return m_velocity; }

  double getMass() const { return m_mass; };

  virtual ~Movable() = default;

private:
  const double    m_mass;
  math::Vec       m_velocity;
};

} // namespace sim

#endif /* movable.h */
