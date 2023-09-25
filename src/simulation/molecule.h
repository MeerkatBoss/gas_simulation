/**
 * @file molecule.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief
 *
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_MOLECULE_H
#define __SIMULATION_MOLECULE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include "math/transform.h"
#include "simulation/scene_object.h"
#include "simulation/movable.h"

namespace sim
{

// Forward declaration
class ReactionBuilder;

class Molecule : public SceneObject, public Movable
{
public:
  Molecule(const sf::Texture&     texture,
                 double           mass      = 1,
           const math::Vec&       velocity  = math::Vec(),
           const math::Transform& transform = math::Transform()) :
    SceneObject(transform), Movable(mass, velocity),
    m_sprite(texture)
  {
    m_sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2,
                                    texture.getSize().y / 2));
  }

  virtual bool isMovable() const override { return true; }

  virtual Movable* asMovable() override { return this; }

  virtual bool isTickable() const override { return true; }

  virtual void updateTick(double delta_time_seconds) override
  {
    transform().move(velocity() * delta_time_seconds);
  }

  virtual void addToReaction(ReactionBuilder& builder) const = 0;

  virtual void collide(SceneObject& other) override;
  
  virtual void draw(ui::Canvas& window,
                    const math::Transform& parent_transform) const override;

  virtual ~Molecule() = default;
private:
  mutable sf::Sprite m_sprite;
};

} // namespace sim

#endif /* molecule.h */
