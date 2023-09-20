/**
 * @file molecule_controller.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-19
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_MOLECULE_CONTROLLER_H
#define __SIMULATION_MOLECULE_CONTROLLER_H

#include <cstddef>

#include "math/vec.h"
#include "math/transform.h"
#include "simulation/circle_molecule.h"
#include "simulation/square_molecule.h"
#include "simulation/scene.h"
#include "simulation/reaction_builder.h"
#include "util/dyn_array.h"

namespace sim
{

class MoleculeController
{
public:
  MoleculeController(Scene& scene,
                     double molecule_size,
                     const math::Point& spawn_point,
                     const math::Vec& spawn_velocity) :
    m_scene(scene),
    m_molecules(),
    m_reactionBuilder(),
    m_spawnTransform(spawn_point, math::Vec(molecule_size, molecule_size)),
    m_spawnVelocity(spawn_velocity)
  {}

  CircleMolecule* spawnCircle()
  {
    CircleMolecule* spawned = m_scene.createObject<CircleMolecule>(
                                                    m_spawnVelocity,
                                                    m_spawnTransform);
    m_molecules.pushBack(spawned);
    return spawned;
  }

  SquareMolecule* spawnSquare()
  {
    SquareMolecule* spawned = m_scene.createObject<SquareMolecule>(
                                                    2,
                                                    m_spawnVelocity,
                                                    m_spawnTransform);
    m_molecules.pushBack(spawned);
    return spawned;
  }

  template<typename TReaction, typename... TArgs>
  void addReactionTemplate(const TArgs&... args)
  {
    m_reactionBuilder.addReactionTemplate<TReaction>(args...);
  }

  void runReactions();

  ~MoleculeController() = default;

private:
  Scene&                    m_scene;
  util::DynArray<Molecule*> m_molecules;
  ReactionBuilder           m_reactionBuilder;

  math::Transform m_spawnTransform;
  math::Vec       m_spawnVelocity;

  void compactMoleculeStorage();

};

} // namespace sim

#endif /* molecule_controller.h */
