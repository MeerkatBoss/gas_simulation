#include "ui/button.h"
#include "ui/widget.h"

namespace ui
{

void Button::handleMouseEvent(
              const MouseEvent& event,
              const math::Transform&  parent_transform)
{
  if (event.button != MouseEvent::Button::Left)
    return;

  if (m_pressed && event.type == MouseEvent::Type::Release)
  {
    m_controller.onRelease(getId());
    m_pressed = false;
    return;
  }

  if (event.type == MouseEvent::Type::Click
      && containsPoint(event.position, parent_transform))
  {
    m_controller.onClick(getId());
    m_pressed = true;
    return;
  }
}

void Button::draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform)
{
  if (m_pressed)
    m_controller.onHold(getId());

  math::Transform realTransform = parent_transform * transform();
  
  m_sprite.setRotation(realTransform.getAngleDeg());
  m_sprite.setPosition(realTransform.getPosition());

  math::Vec targetScale = realTransform.getScale();

  targetScale.x /= m_sprite.getTexture()->getSize().x;
  targetScale.y = targetScale.x;
  
  // targetScale.y /= m_sprite.getTexture()->getSize().y;
  m_sprite.setScale(targetScale);

  draw_target.draw(m_sprite);
}

} // namespace ui
