#include "simulation/circle_molecule.h"

#include "simulation/intersection_builder.h"
#include "simulation/reaction_builder.h"

namespace sim
{

void SquareMolecule::addToReaction(ReactionBuilder& builder) const
{
  builder.addSquareMolecule(this);
}

void SquareMolecule::addToIntersection(IntersectionBuilder& builder) const
{
  builder.addSquare(this);
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
