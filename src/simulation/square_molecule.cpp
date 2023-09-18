#include "simulation/circle_molecule.h"

#include "simulation/reaction_builder.h"

namespace sim
{

void SquareMolecule::addToReaction(ReactionBuilder& builder) const
{
  builder.addSquareMolecule(this);
}

BoundingBox SquareMolecule::getBoundingBox() const
{
  const double angle = transform().getAngleDeg() / 180 * M_PI;
  const double cosine = cos(angle);
  const double sine   = sin(angle);
  const math::Vec center = transform().getPosition();
  const math::Vec scale  = transform().getScale();

  const double extent_x = (fabs(scale.x * cosine) + fabs(scale.y * cosine)) / 2;
  const double extent_y = (fabs(scale.x * sine)   + fabs(scale.y * sine))   / 2;

  return BoundingBox {
    .xMax = center.x + extent_x,
    .xMin = center.x - extent_x,
    .yMax = center.y + extent_y,
    .yMin = center.y - extent_y
  };
}

void SquareMolecule::draw(ui::RenderWindow& window) const
{
  sf::RectangleShape square;
  square.setSize(math::Vec(1, 1));
  square.setOrigin(math::Vec(0.5, 0.5));
  square.setPosition(transform().getPosition());
  square.setScale(transform().getScale());
  square.setFillColor(sf::Color::Red);
  window.renderTexture().draw(square);
}

} // namespace sim
