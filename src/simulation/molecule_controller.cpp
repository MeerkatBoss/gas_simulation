#include "simulation/molecule_controller.h"

#include <cstdio>
#include <cstdlib>

#include "simulation/circle_molecule.h"
#include "simulation/molecule.h"
#include "simulation/reaction_builder.h"

namespace sim
{

void MoleculeController::onHold(size_t button_id)
{
  if (button_id != m_circleButtonId &&
      button_id != m_squareButtonId)
  {
    return;
  }

  double delta = m_clock.restart().asSeconds();

  m_circleSeconds += delta;
  m_squareSeconds += delta;

  while (button_id == m_circleButtonId && m_circleSeconds > m_spawnDelay)
  {
    spawnCircle();
    m_circleSeconds -= m_spawnDelay;
  }

  while (button_id == m_squareButtonId && m_squareSeconds > m_spawnDelay)
  {
    spawnSquare();
    m_squareSeconds -= m_spawnDelay;
  }
}

math::Vec MoleculeController::getSpawnVelocity() const
{
  const double angle = (double(rand()) / RAND_MAX - 0.5) * 2 * m_spreadAngleDeg;
  const double scale = (double(rand()) / RAND_MAX - 0.5) * 0.2 + 1;

  return math::Transform(math::Vec(), math::Vec(scale, scale), angle)
         * m_spawnVelocity;
}

void MoleculeController::runReactions()
{
  size_t molecule_count = m_molecules.getSize();
  for (size_t first = 0; first < molecule_count; ++first)
  {
    if (m_molecules[first] == nullptr)
    {
      continue;
    }

    for (size_t second = first + 1; second < molecule_count; ++second)
    {
      if (m_molecules[second] == nullptr)
      {
        continue;
      }
      if(!m_molecules[first]->intersects(*m_molecules[second]))
      {
        continue;
      }
      
      m_reactionBuilder.addMolecule(*m_molecules[first]);
      m_reactionBuilder.addMolecule(*m_molecules[second]);

      Reaction* started = m_reactionBuilder.buildReaction();
      if (started == nullptr)
      {
        continue;
      }

      while (started->hasNextResult())
      {
        started->spawnNextResult();
      }

      delete started;

      m_molecules[first]->kill();
      m_molecules[first] = nullptr;
      
      m_molecules[second]->kill();
      m_molecules[second] = nullptr;

      break;
    }
  }

  compactMoleculeStorage();
}

void MoleculeController::compactMoleculeStorage()
{
  size_t idx = 0;
  
  while (idx < m_molecules.getSize())
  {
    // Find last non-null
    while (!m_molecules.isEmpty() && m_molecules.back() == nullptr)
    {
      m_molecules.popBack();
    }

    if (idx > m_molecules.getSize())
    {
      break;
    }

    // Find first null
    while (idx < m_molecules.getSize() && m_molecules[idx] != nullptr)
    {
      ++ idx;
    }

    // If found null
    if (idx < m_molecules.getSize())
    {
      m_molecules[idx] = m_molecules.back();
      m_molecules.popBack();
    }
  }
}

} // namespace sim
