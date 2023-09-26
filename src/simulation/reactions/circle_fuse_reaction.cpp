#include "simulation/reactions/circle_fuse_reaction.h"

#include "simulation/molecule_controller.h"

namespace sim
{

void CircleFuseReaction::spawnNextResult()
{
  SquareMolecule* molecule = m_controller.spawnSquare(2);
  molecule->velocity() = m_velocity;
  molecule->transform().setPosition(m_position);
  m_spawned = true;
}

} // namespace sim
