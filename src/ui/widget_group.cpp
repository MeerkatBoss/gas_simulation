#include "ui/widget_group.h"
#include "math/transform.h"
#include "ui/widget.h"

namespace ui
{

void WidgetGroup::handleMouseEvent(
            const MouseEvent& event,
            const math::Transform&  parent_transform)
{
  math::Transform realTransform = parent_transform * transform();
  for (size_t i = 0; i < m_children.getSize(); ++i)
  {
    m_children[i]->handleMouseEvent(event, realTransform);
  }
}
void WidgetGroup::draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform)
{
  math::Transform realTransform = parent_transform * transform();
  for (size_t i = 0; i < m_children.getSize(); ++i)
  {
    m_children[i]->draw(draw_target, realTransform);
  }
}

} // namespace ui
