/**
 * @file widget.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-15
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __WIDGETS_WIDGET_H
#define __WIDGETS_WIDGET_H

#include <cstddef>

#include <SFML/Graphics.hpp>

#include "math/transform.h"
#include "math/vec.h"

namespace ui
{

struct MouseEvent
{
  enum class Type {
    None,
    Hover,
    Click,
    Hold,
    Release
  };

  enum class Button {
    None,
    Left,
    Right,
    Middle
  };
  
  Type      type;
  Button    button;
  math::Vec position;

  static MouseEvent getMouseEvent(const sf::RenderWindow& sfml_window,
                                  const sf::Event&        sfml_event);
};

class Widget
{
public:
  Widget(const math::Transform& transform = math::Transform()) :
    m_transform(transform),
    m_id(++s_idCounter)
  {
  }


  const math::Transform& transform() const { return m_transform; }
        math::Transform& transform()       { return m_transform; }

  size_t getId() const { return m_id; }

  virtual void handleMouseEvent(
              const MouseEvent& event,
              const math::Transform&  parent_transform = math::Transform()) = 0;

  virtual void draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform = math::Transform()) = 0;

  virtual ~Widget() = default;

protected:
  virtual bool containsPoint(
                  const math::Point& point,
                  const math::Transform&  parent_transform = math::Transform());
                          
private:
  static size_t s_idCounter;

  math::Transform m_transform;
  size_t          m_id;
};

} // namespace ui


#endif /* widget.h */
