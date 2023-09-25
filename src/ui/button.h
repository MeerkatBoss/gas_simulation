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

#include <cstddef>

#include <SFML/Graphics/Texture.hpp>

#include "math/transform.h"
#include "ui/widget.h"
namespace ui
{

class ButtonController
{
public:
  virtual void onClick([[maybe_unused]] size_t button_id) { return; }
  virtual void onHold([[maybe_unused]] size_t button_id) { return; }
  virtual void onRelease([[maybe_unused]] size_t button_id) { return; }

  virtual ~ButtonController() = default;
};

class Button : public Widget
{
public:
  Button(ButtonController& controller,
         const sf::Texture& texture,
         double width = 1,
         const math::Point& position = math::Point(),
         double angle = 0) :
    Widget(math::Transform(
            position,
            math::Vec(width,
                      width / texture.getSize().x * texture.getSize().y),
            angle)),
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
