/**
 * @file widget_group.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-22
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __UI_WIDGET_GROUP_H
#define __UI_WIDGET_GROUP_H

#include "math/transform.h"
#include "ui/widget.h"
#include "util/dyn_array.h"
#include <cstdio>

namespace ui
{

class WidgetGroup : public Widget
{
public:
  WidgetGroup(math::Transform transform = math::Transform()) :
    Widget(transform)
  {
  }

  /*
  template<typename TWidget, typename... TArgs>
  TWidget* createWidget(TArgs&&... args)
  {
    TWidget* widget = new TWidget(args...);
    m_children.pushBack(widget);
    fprintf(stderr, "%p\n", (void*)widget);
    return widget;
  }
  */

  void captureWidget(Widget* widget)
  {
    m_children.pushBack(widget);
  }

  void handleMouseEvent(
              const MouseEvent& event,
              const math::Transform&  parent_transform = math::Transform())
    override;

  virtual void draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform = math::Transform())
    override;

  virtual ~WidgetGroup() override
  {
    for (size_t i = 0; i < m_children.getSize(); ++i)
    {
      delete m_children[i];
    }
  }

private:
  util::DynArray<Widget*> m_children;
};

} // namespace ui

#endif /* widget_group.h */
