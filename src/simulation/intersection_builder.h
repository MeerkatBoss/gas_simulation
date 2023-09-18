/**
 * @file intersection_builder.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_INTERSECTION_BUILDER_H
#define __SIMULATION_INTERSECTION_BUILDER_H

#include "simulation/molecule.h"
#include "simulation/circle_molecule.h"
#include "simulation/square_molecule.h"

namespace sim
{

class IntersectionBuilder
{
public:
  IntersectionBuilder(const Molecule& first, const Molecule& second) :
    m_circleCount(0), m_squareCount(0)
  {
    addMolecule(first);
    addMolecule(second);
  }

  bool hasIntersection() const;

  ~IntersectionBuilder() = default;
private:
  const CircleMolecule* m_circles[2];
  const SquareMolecule* m_squares[2];

  size_t m_circleCount;
  size_t m_squareCount;

  void addMolecule(const Molecule& molecule)
  {
    molecule.addToIntersection(*this);
  }

  friend
    void CircleMolecule::addToIntersection(IntersectionBuilder& builder) const;

  void addCircle(const CircleMolecule* circle)
  {
    m_circles[m_circleCount] = circle;
    ++ m_circleCount;
  }

  friend
    void SquareMolecule::addToIntersection(IntersectionBuilder& builder) const;

  void addSquare(const SquareMolecule* square)
  {
    m_squares[m_squareCount] = square;
    ++ m_squareCount;
  }

};

} // namespace sim

#endif /* intersection_builder.h */
