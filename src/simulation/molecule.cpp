#include "simulation/molecule.h"

namespace sim
{

void Molecule::collide(SceneObject& other)
{
  using math::Vec;
  using math::Point;

  if (!other.isMovable())
  {
    other.collide(*this);
    return;
  }

  Movable* otherMovable = other.asMovable();

  const Point x1 = transform().getPosition();
  const Point x2 = other.transform().getPosition();
  const Vec delta = x1 - x2;

  const Vec v1 = velocity();
  const Vec v2 = otherMovable->velocity();
  const double m1 = getMass();
  const double m2 = otherMovable->getMass();

  const Vec v1_x = v1.projectOn(delta);
  const Vec v2_x = v2.projectOn(delta);

  // If objects are flying away from each other
  if (Vec::dotProduct(v1, x2 - x1) < 0 &&
      Vec::dotProduct(v2, x1 - x2) < 0)
  {
    return;
  }

  velocity() = 
    v1 - (2 * m2) / (m1 + m2) * (v1_x - v2_x);
  otherMovable->velocity() = 
    v2 - (2 * m1) / (m1 + m2) * (v2_x - v1_x);
}

void Molecule::draw(ui::Canvas& window,
                    const math::Transform& parent_transform) const
{
  math::Transform realTransform = parent_transform * transform();

  math::Vec scale = realTransform.getScale();
  scale.x /= m_sprite.getTexture()->getSize().x;
  scale.y /= m_sprite.getTexture()->getSize().y;

  m_sprite.setScale(scale);
  m_sprite.setRotation(realTransform.getAngleDeg());
  m_sprite.setPosition(realTransform.getPosition());

  window.renderTexture().draw(m_sprite);
}

} // namespace sim
