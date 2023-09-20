/**
 * @file render_window.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __UI_RENDER_WINDOW_H
#define __UI_RENDER_WINDOW_H

#include <SFML/Graphics/RenderTexture.hpp>
#include "math/transform.h"
#include "ui/widget.h"

namespace ui
{

class Canvas : public Widget
{
public:
  Canvas(size_t width_px, size_t height_px,
               const math::Transform& transform = math::Transform()) :
    Widget(transform)
  {
    m_renderTexture.create(width_px, height_px);
  }

  void handleMouseEvent(const MouseEvent&) override { return; };

  void draw(      sf::RenderTarget& draw_target,
            const math::Transform&  parent_transform = math::Transform())
    override;

  const sf::RenderTexture& renderTexture() const { return m_renderTexture; }
        sf::RenderTexture& renderTexture()       { return m_renderTexture; }

private:
  sf::RenderTexture m_renderTexture;
};

} // namespace ui

#endif /* render_window.h */
