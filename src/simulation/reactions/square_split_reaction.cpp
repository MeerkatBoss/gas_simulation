#include "simulation/reactions/square_split_reaction.h"

#include <cmath>
#include <cstdlib>
#include <math.h>
#include "simulation/circle_molecule.h"
#include "simulation/molecule_controller.h"

namespace sim
{

void SquareSplitReaction::spawnNextResult()
{
  const size_t molecule_count = size_t(m_mass);
  const double angle_delta = 2*M_PI / molecule_count;

  double angle = double(rand()) / RAND_MAX * M_PI / molecule_count;
  double speed = m_velocity.length();
  for (size_t i = 0; i < molecule_count; ++i)
  {
    CircleMolecule* molecule = m_controller.spawnCircle();
    molecule->velocity() = speed * math::Vec(cos(angle), sin(angle));
    molecule->transform().setPosition(m_position);
    angle += angle_delta;
  }

  m_spawned = true;
}

} // namespace sim
