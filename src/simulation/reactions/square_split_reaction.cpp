#include "simulation/reactions/square_split_reaction.h"

#include <cmath>
#include <math.h>
#include "simulation/circle_molecule.h"
#include "simulation/molecule_controller.h"

namespace sim
{

void SquareSplitReaction::spawnNextResult()
{
  const size_t molecule_count = size_t(m_mass);
  const double angle_delta = 2*M_PI / molecule_count;

  double angle = 0;
  double speed = 1.2;
  for (size_t i = 0; i < molecule_count; ++i)
  {
    CircleMolecule* molecule = m_controller.spawnCircle();
    molecule->velocity() = speed * math::Vec(cos(angle), sin(angle))
                           + m_velocity;
    molecule->transform().setPosition(m_position
                                      + 0.25 * molecule_count
                                          * math::Vec(cos(angle), sin(angle)));
    angle += angle_delta;
  }

  m_spawned = true;
}

} // namespace sim
