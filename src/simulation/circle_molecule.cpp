#include "simulation/circle_molecule.h"

#include "simulation/intersection_builder.h"
#include "simulation/reaction_builder.h"

namespace sim
{

void CircleMolecule::addToReaction(ReactionBuilder& builder) const
{
  builder.addCircleMolecule(this);
}

void CircleMolecule::addToIntersection(IntersectionBuilder& builder) const
{
  builder.addCircle(this);
}

void CircleMolecule::draw(ui::RenderWindow& window) const
{
  sf::CircleShape circle;
  circle.setRadius(0.5);
  circle.setPosition(transform().getPosition());
  circle.setScale(transform().getScale());
  circle.setFillColor(sf::Color::Yellow);
  window.renderTexture().draw(circle);
}

} // namespace sim
