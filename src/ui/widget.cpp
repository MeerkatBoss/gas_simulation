#include "ui/widget.h"
#include "math/transform.h"

namespace ui
{

using math::Vec;

static bool s_pressedButtons[4]
  = { false, false, false, false};

static MouseEvent::Button getPressedButton()
{
  for (size_t i = 0; i < 4; ++i)
    if (s_pressedButtons[i])
      return MouseEvent::Button(i);
  return MouseEvent::Button::None;
}

static MouseEvent getMousePressEvent(const sf::RenderWindow& sfml_window,
                                     const sf::Event::MouseButtonEvent&
                                       sfml_event);
static MouseEvent getMouseReleaseEvent(const sf::RenderWindow& sfml_window,
                                       const sf::Event::MouseButtonEvent&
                                         sfml_event);
static MouseEvent getMouseHoldEvent(const sf::RenderWindow& sfml_window,
                                       const sf::Event::MouseMoveEvent&
                                         sfml_event);

MouseEvent MouseEvent::getMouseEvent(const sf::RenderWindow& sfml_window,
                                     const sf::Event&  sfml_event)
{
   if (sfml_event.type == sf::Event::MouseButtonPressed)
     return getMousePressEvent(sfml_window, sfml_event.mouseButton);
   if (sfml_event.type == sf::Event::MouseButtonReleased)
     return getMouseReleaseEvent(sfml_window, sfml_event.mouseButton);
   if (sfml_event.type == sf::Event::MouseMoved)
     return getMouseHoldEvent(sfml_window, sfml_event.mouseMove);
  
   return MouseEvent{
      .type = MouseEvent::Type::None,
      .button = MouseEvent::Button::None,
      .position = Vec(0, 0)
   };
}

static MouseEvent getMousePressEvent(const sf::RenderWindow& sfml_window,
                                     const sf::Event::MouseButtonEvent&
                                       sfml_event)
{
  MouseEvent::Button button = MouseEvent::Button::None;
  switch (sfml_event.button)
  {
  case sf::Mouse::Button::Left: 
    button = MouseEvent::Button::Left; 
    break;
  case sf::Mouse::Button::Right: 
    button = MouseEvent::Button::Right; 
    break;
  case sf::Mouse::Button::Middle: 
    button = MouseEvent::Button::Middle; 
    break;
  case sf::Mouse::Button::XButton1: 
  case sf::Mouse::Button::XButton2: 
  case sf::Mouse::Button::ButtonCount: 
  default:
    break;
  }
  if (button != MouseEvent::Button::None)
  {
    s_pressedButtons[size_t(button)] = true;
  }
  sf::Vector2f coords = sfml_window.mapPixelToCoords(sf::Vector2i(
                                                      sfml_event.x,
                                                      sfml_event.y));
  return MouseEvent{
    .type     = MouseEvent::Type::Click,
    .button   = button,
    .position = Vec(coords.x, coords.y)
  };
}

static MouseEvent getMouseReleaseEvent(const sf::RenderWindow& sfml_window,
                                       const sf::Event::MouseButtonEvent&
                                         sfml_event)
{
  MouseEvent::Button button = MouseEvent::Button::None;
  switch (sfml_event.button)
  {
  case sf::Mouse::Button::Left: 
    button = MouseEvent::Button::Left; 
    break;
  case sf::Mouse::Button::Right: 
    button = MouseEvent::Button::Right; 
    break;
  case sf::Mouse::Button::Middle: 
    button = MouseEvent::Button::Middle; 
    break;
  case sf::Mouse::Button::XButton1: 
  case sf::Mouse::Button::XButton2: 
  case sf::Mouse::Button::ButtonCount: 
  default:
    break;
  }
  if (button != MouseEvent::Button::None)
  {
    s_pressedButtons[size_t(button)] = true;
  }
  sf::Vector2f coords = sfml_window.mapPixelToCoords(sf::Vector2i(
                                                      sfml_event.x,
                                                      sfml_event.y));
  return MouseEvent{
    .type     = MouseEvent::Type::Release,
    .button   = button,
    .position = Vec(coords.x, coords.y)
  };
}

static MouseEvent getMouseHoldEvent(const sf::RenderWindow& sfml_window,
                                       const sf::Event::MouseMoveEvent&
                                         sfml_event)
{
  MouseEvent::Button button = getPressedButton();
  sf::Vector2f coords = sfml_window.mapPixelToCoords(sf::Vector2i(
                                                      sfml_event.x,
                                                      sfml_event.y));
  return MouseEvent{
    .type = (button == MouseEvent::Button::None)
              ? MouseEvent::Type::Hover
              : MouseEvent::Type::Hold,

    .button   = button,
    .position = Vec(coords.x, coords.y)
  };

}

bool Widget::containsPoint(
                  const math::Point& point,
                  const math::Transform&  parent_transform)
{
  math::Transform realTransform = parent_transform * transform();
  math::Point localPoint = (realTransform.getInverse() * point);

  return 0 < localPoint.x && localPoint.x < 1 &&
         0 < localPoint.y && localPoint.y < 1;
}

} // namespace ui
