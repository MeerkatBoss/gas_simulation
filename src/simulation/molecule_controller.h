/**
 * @file molecule_controller.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 * @version 0.1 @date 2023-09-19
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_MOLECULE_CONTROLLER_H
#define __SIMULATION_MOLECULE_CONTROLLER_H

#include <cstddef>
#include <cmath>

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
                     double molecule_size = 1,
                     const math::Point& spawn_point = math::Point(0, 0),
                     const math::Vec& spawn_velocity = math::Vec::UnitY,
                     double spread_angle = 0) :
    m_scene(scene),
    m_molecules(),
    m_reactionBuilder(),
    m_spawnTransform(spawn_point, math::Vec(molecule_size, molecule_size)),
    m_spawnVelocity(spawn_velocity),
    m_spreadAngleDeg(spread_angle)
  {}

  CircleMolecule* spawnCircle()
  {
    CircleMolecule* spawned = m_scene.createObject<CircleMolecule>(
                                                    getSpawnVelocity(),
                                                    m_spawnTransform);
    m_molecules.pushBack(spawned);
    return spawned;
  }

  SquareMolecule* spawnSquare()
  {
    SquareMolecule* spawned = m_scene.createObject<SquareMolecule>(
                                                    2,
                                                    getSpawnVelocity(),
                                                    m_spawnTransform);
    m_molecules.pushBack(spawned);
    return spawned;
  }

  template<typename TReaction, typename... TArgs>
  void addReactionTemplate(const TArgs&... args)
  {
    m_reactionBuilder.addReactionTemplate<TReaction>(args...);
  }

  void setSpawnPoint(const math::Point& spawn_point)
  {
    m_spawnTransform.setPosition(spawn_point);
  }

  void setSpawnScale(double scale)
  {
    m_spawnTransform.setScale(math::Vec(scale, scale));
  }

  void setSpawnVelocity(const math::Vec& velocity)
  {
    m_spawnVelocity = velocity;
  }

  void setSpread(double angle_deg)
  {
    m_spreadAngleDeg = angle_deg;
  }

  void runReactions();

  ~MoleculeController() = default;

private:
  Scene&                    m_scene;
  util::DynArray<Molecule*> m_molecules;
  ReactionBuilder           m_reactionBuilder;

  math::Transform m_spawnTransform;
  math::Vec       m_spawnVelocity;
  double          m_spreadAngleDeg;

  math::Vec getSpawnVelocity() const;

  void compactMoleculeStorage();
};

} // namespace sim

#endif /* molecule_controller.h */
