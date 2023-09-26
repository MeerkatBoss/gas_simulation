#include "simulation/reactions/circle_absorb_reaction.h"

#include "simulation/molecule_controller.h"

namespace sim
{

void CircleAbsorbReaction::spawnNextResult()
{
  SquareMolecule* molecule = m_controller.spawnSquare(m_mass);
  molecule->velocity() = m_velocity;
  molecule->transform().setPosition(m_position);
  m_spawned = true;
}

} // namespace sim
