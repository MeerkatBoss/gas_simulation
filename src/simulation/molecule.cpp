#include "simulation/molecule.h"

namespace sim
{

void Molecule::collide(SceneObject& other)
{
  using math::Vec;

  if (!other.isMovable())
  {
    return;
  }

  Movable* otherMovable = other.asMovable();
  const Vec delta = other.transform().getPosition() - transform().getPosition();

  const Vec v1 = velocity();
  const Vec v2 = otherMovable->velocity();
  const double m1 = getMass();
  const double m2 = otherMovable->getMass();

  otherMovable->velocity() = 
    v2 - (2 * m1) / (m1 + m2) * (v2 - v1).projectOn(delta);
  velocity() = 
    v1 - (2 * m2) / (m1 + m2) * (v1 - v2).projectOn(delta);
}

} // namespace sim
