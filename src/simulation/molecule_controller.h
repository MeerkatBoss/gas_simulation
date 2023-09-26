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

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <cstddef>
#include <cmath>

#include "math/vec.h"
#include "math/transform.h"
#include "simulation/circle_molecule.h"
#include "simulation/square_molecule.h"
#include "simulation/scene.h"
#include "simulation/reaction_builder.h"
#include "ui/button.h"
#include "ui/slider.h"
#include "util/dyn_array.h"

namespace sim
{

class MoleculeController : public ui::ButtonController,
                           public ui::SliderController
{
public:
  MoleculeController(Scene& scene,
                     const sf::Texture& circle_texture,
                     const sf::Texture& square_texture) :
    m_scene(scene),
    m_circleTexture(circle_texture),
    m_squareTexture(square_texture),
    m_molecules(),
    m_reactionBuilder(),
    m_spawnTransform(),
    m_spawnVelocity(math::Vec::UnitY),
    m_spreadAngleDeg(0),
    m_spawnDelay(INFINITY),
    m_circleButtonId(0),
    m_squareButtonId(0)
  {}

  CircleMolecule* spawnCircle()
  {
    CircleMolecule* spawned = m_scene.createObject<CircleMolecule>(
                                                    m_circleTexture,
                                                    getSpawnVelocity(),
                                                    m_spawnTransform);
    m_molecules.pushBack(spawned);
    return spawned;
  }

  SquareMolecule* spawnSquare(double mass = 2)
  {
    SquareMolecule* spawned = m_scene.createObject<SquareMolecule>(
                                                    m_squareTexture,
                                                    mass,
                                                    getSpawnVelocity(),
                                                    m_spawnTransform);
    m_molecules.pushBack(spawned);
    return spawned;
  }

  void addReactionTemplate(ReactionTemplate* reaction)
  {
    m_reactionBuilder.addReactionTemplate(reaction);
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

  void setSpawnRate(double molecules_per_second)
  {
    if (fabs(molecules_per_second) < 1e-6)
    {
      m_spawnDelay = INFINITY;
      return;
    }

    m_spawnDelay = 1.0 / fabs(molecules_per_second);
  }

  void setCircleButton(size_t button_id)
  {
    m_circleButtonId = button_id;
  }

  void setSquareButton(size_t button_id)
  {
    m_squareButtonId = button_id;
  }

  void onClick(size_t button_id) override
  {
    if (button_id != m_circleButtonId &&
        button_id != m_squareButtonId)
    {
      return;
    }

    double delta = m_clock.restart().asSeconds();
    m_circleSeconds += delta;
    m_squareSeconds += delta;

    if (button_id == m_circleButtonId)
      m_circleSeconds = 0;
    else
      m_squareSeconds = 0;
  }
  void onHold(size_t button_id) override;

  void onSetVal(double value) override
  {
    m_spawnVelocity *= value / m_spawnVelocity.length();
  }

  double getMaxVal() override { return 11; }

  double getMinVal() override { return 1; }

  double getCurVal() override
  {
    return m_spawnVelocity.length();
  }

  void runReactions();

  ~MoleculeController() = default;

private:
  Scene&                    m_scene;
  const sf::Texture& m_circleTexture;
  const sf::Texture& m_squareTexture;

  util::DynArray<Molecule*> m_molecules;
  ReactionBuilder           m_reactionBuilder;

  math::Transform m_spawnTransform;
  math::Vec       m_spawnVelocity;
  double          m_spreadAngleDeg;
  double          m_spawnDelay;

  size_t m_circleButtonId;
  size_t m_squareButtonId;

  double m_circleSeconds;
  double m_squareSeconds;

  sf::Clock m_clock;

  math::Vec getSpawnVelocity() const;

  void compactMoleculeStorage();
};

} // namespace sim

#endif /* molecule_controller.h */
