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

class MoleculeController;

struct Reagents
{
  util::DynArray<const CircleMolecule*> circles;
  util::DynArray<const SquareMolecule*> squares;
};

class Reaction
{
public:
  Reaction(MoleculeController& controller) :
    m_controller(controller)
  {
  }

  virtual bool hasNextResult() const = 0;
  virtual void spawnNextResult() = 0;
  
  virtual ~Reaction() = default;
protected:
  MoleculeController& m_controller;
};

class ReactionTemplate
{
public:
  ReactionTemplate(MoleculeController& controller) :
    m_controller(controller)
  {
  }

  virtual Reaction* startReaction(const Reagents& reagents) = 0;

  virtual ~ReactionTemplate() = default;
protected:
  MoleculeController& m_controller;
};

class ReactionBuilder
{
public:
  ReactionBuilder() = default;

  void addMolecule(const Molecule& molecule)
  {
    molecule.addToReaction(*this);
  }

  void addReactionTemplate(ReactionTemplate* reaction)
  {
    m_reactions.pushBack(reaction);
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
