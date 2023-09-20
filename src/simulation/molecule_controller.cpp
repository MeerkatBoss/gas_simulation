#include "simulation/molecule_controller.h"
#include "simulation/circle_molecule.h"
#include "simulation/molecule.h"
#include "simulation/reaction_builder.h"

namespace sim
{

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
        Molecule* result = started->getNextResult();
        m_scene.captureObject(result);
        m_molecules.pushBack(result);
      }

      m_molecules[first]->kill();
      m_molecules[first] = nullptr;
      
      m_molecules[second]->kill();
      m_molecules[second] = nullptr;
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
