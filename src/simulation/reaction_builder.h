/**
 * @file reaction_builder.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_REACTION_BUILDER_H
#define __SIMULATION_REACTION_BUILDER_H

#include "simulation/molecule.h"
#include "simulation/circle_molecule.h"
#include "simulation/square_molecule.h"

#include "util/dyn_array.h"

namespace sim
{
struct Reagents
{
  util::DynArray<const CircleMolecule*> circles;
  util::DynArray<const SquareMolecule*> squares;
};

class Reaction
{
public:
  Reaction(double energy_produced) : m_energyProduced(energy_produced) {}

  double getEnergyProduced() const { return m_energyProduced; }

  virtual bool      hasNextResult() const = 0;
  virtual Molecule* getNextResult()       = 0;
  
  virtual ~Reaction() = default;
private:
  const double m_energyProduced;
};

class ReactionTemplate
{
public:
  virtual Reaction* startReaction(const Reagents& reagents) = 0;

  virtual ~ReactionTemplate() = default;
};

class ReactionBuilder
{
public:
  ReactionBuilder() = default;

  void addMolecule(const Molecule& molecule)
  {
    molecule.addToReaction(*this);
  }

  template<typename TReaction, typename... TArgs>
  void addReactionTemplate(const TArgs&... args)
  {
    m_reactions.pushBack(new TReaction(args...));
  }

  Reaction* buildReaction();

  ~ReactionBuilder()
  {
    for (size_t i = 0; i < m_reactions.getSize(); ++i)
      delete m_reactions[i];
  }

private:
  Reagents m_reagents;
  util::DynArray<ReactionTemplate*> m_reactions;

  friend void CircleMolecule::addToReaction(ReactionBuilder&) const;
  void addCircleMolecule(const CircleMolecule* molecule)
  {
    m_reagents.circles.pushBack(molecule);
  }

  friend void SquareMolecule::addToReaction(ReactionBuilder&) const;
  void addSquareMolecule(const SquareMolecule* molecule)
  {
    m_reagents.squares.pushBack(molecule);
  }
};


} // namespace sim

#endif /* reaction_builder.h */
