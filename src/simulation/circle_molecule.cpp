#include "simulation/circle_molecule.h"

#include "simulation/reaction_builder.h"

namespace sim
{

void CircleMolecule::addToReaction(ReactionBuilder& builder) const
{
  builder.addCircleMolecule(this);
}

BoundingBox CircleMolecule::getBoundingBox() const
{
  const double angle = transform().getAngleDeg() / 180 * M_PI;
  const double cosine = cos(angle);
  const double sine   = sin(angle);
  const math::Vec center = transform().getPosition();
  const math::Vec scale  = transform().getScale();

  const double extent_x = hypot(scale.x * cosine, scale.y * sine) / 2;
  const double extent_y = hypot(scale.x * sine,   scale.y * cosine) / 2;

  return BoundingBox {
    .xMax = center.x + extent_x,
    .xMin = center.x - extent_x,
    .yMax = center.y + extent_y,
    .yMin = center.y - extent_y
  };
}

void CircleMolecule::draw(ui::Canvas& window,
                          const math::Transform& parent_transform) const
{
  math::Transform realTransform = parent_transform * transform();

  sf::CircleShape circle;
  circle.setRadius(0.5);
  circle.setOrigin(sf::Vector2f(0.5, 0.5));
  circle.setPosition(realTransform.getPosition());
  circle.setScale(realTransform.getScale());
  circle.setFillColor(sf::Color::Yellow);
  circle.setOutlineThickness(0.05);
  circle.setOutlineColor(sf::Color::Black);

  window.renderTexture().draw(circle);
}

} // namespace sim
