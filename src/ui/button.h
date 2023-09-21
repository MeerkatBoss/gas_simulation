/**
 * @file button.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-21
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __UI_BUTTON_H
#define __UI_BUTTON_H

#include <SFML/Graphics/Texture.hpp>
#include "ui/widget.h"
namespace ui
{

class ButtonController
{
public:
  virtual void onClick() { return; }
  virtual void onHold() { return; }
  virtual void onRelease() { return; }

  virtual ~ButtonController() = default;
};

class Button : public Widget
{
public:
  Button(ButtonController& controller,
         const sf::Texture& texture,
         const math::Transform& transform = math::Transform()) :
    Widget(transform),
    m_sprite(texture),
    m_controller(controller),
    m_pressed(false)
  {
  }

  virtual void handleMouseEvent(
              const MouseEvent& event,
              const math::Transform&  parent_transform = math::Transform())
    override;

  virtual void draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform = math::Transform())
    override;

    
private:
  sf::Sprite        m_sprite;
  ButtonController& m_controller;
  bool              m_pressed;
};

} // namespace ui

#endif /* button.h */
