#include "simulation/wall.h"

namespace sim
{

BoundingBox Wall::getBoundingBox() const
{
  const double angle = transform().getAngleDeg() / 180 * M_PI;
  const double cosine = cos(angle);
  const double sine   = sin(angle);
  const math::Vec center = transform().getPosition();
  const math::Vec scale  = transform().getScale();

  const double extent_x = (fabs(scale.x * cosine) + fabs(scale.y * sine))   / 2;
  const double extent_y = (fabs(scale.x * sine)   + fabs(scale.y * cosine)) / 2;

  return BoundingBox {
    .xMax = center.x + extent_x,
    .xMin = center.x - extent_x,
    .yMax = center.y + extent_y,
    .yMin = center.y - extent_y
  };
}


void Wall::collide(SceneObject& other)
{
  if (!other.isMovable())
    return;

  Movable* otherMovable = other.asMovable();

  math::Vec normal = transform().up();
  math::Vec reflected = otherMovable->velocity()
                        - 2*otherMovable->velocity().projectOn(normal);
  otherMovable->velocity() = reflected;
}

void Wall::draw(ui::Canvas& window, const math::Transform& parent_transform)
    const
{
  math::Transform realTransform = parent_transform * transform();

  sf::RectangleShape square;
  square.setSize(math::Vec(1, 1));
  square.setOrigin(math::Vec(0.5, 0.5));
  square.setPosition(realTransform.getPosition());
  square.setScale(realTransform.getScale());
  square.setFillColor(sf::Color::Black);

  window.renderTexture().draw(square);
}

} // namespace sim
