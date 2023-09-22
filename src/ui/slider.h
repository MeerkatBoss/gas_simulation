/**
 * @file slider.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-22
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __UI_SLIDER_H
#define __UI_SLIDER_H

#include <SFML/Graphics/Sprite.hpp>
#include "ui/widget.h"

namespace ui
{

class SliderController
{
public:
  virtual void onSetVal(double) { return; }

  virtual double getMaxVal() = 0;
  virtual double getMinVal() = 0;
  virtual double getCurVal() = 0;

  virtual ~SliderController() = default;
};

class Slider : public Widget
{
public:
  Slider(SliderController& controller,
         const sf::Texture& back_texture,
         const sf::Texture& handle_texture,
         double length = 1,
         math::Vec position = math::Vec(),
         double angle = -90) :
    Widget(math::Transform(
          position,
          math::Vec(
            length / back_texture.getSize().y * back_texture.getSize().x,
            length),
          angle
          )),
    m_background(back_texture),
    m_handle(handle_texture),
    m_controller(controller),
    m_moving(false)
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
  sf::Sprite m_background;
  sf::Sprite m_handle;
  SliderController& m_controller;
  bool m_moving;

  void updateValFromMouse(
              const math::Point& point,
              const math::Transform&  parent_transform = math::Transform());

};

} // namespace sim

#endif /* slider.h */
