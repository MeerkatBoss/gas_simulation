#include "simulation/reaction_builder.h"

namespace sim
{

Reaction* ReactionBuilder::buildReaction()
{
  Reaction* reaction = nullptr;
  for (size_t i = 0; i < m_reactions.getSize(); ++i)
  {
    reaction = m_reactions[i]->startReaction(m_reagents);
    if (reaction != nullptr)
    {
      break;
    }
  }

  m_reagents.circles.clear();
  m_reagents.squares.clear();

  return reaction;
}

} // namespace sim
