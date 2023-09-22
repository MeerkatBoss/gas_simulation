#include "ui/slider.h"
#include "math/transform.h"
#include "ui/widget.h"

namespace ui
{

void Slider::updateValFromMouse(
              const math::Point& point,
              const math::Transform&  parent_transform)
{
    math::Transform realTransform = parent_transform * transform();
    math::Point localPoint = realTransform.getInverse() * point;

    double value = localPoint.y;
    if (value < 0) value = 0;
    if (value > 1) value = 1;

    double length = m_controller.getMaxVal() - m_controller.getMinVal();
    value = m_controller.getMinVal() + value * length;
    
    m_controller.onSetVal(value);

    /*
    using math::Vec;
    Vec top_left = realTransform*Vec(0, 0);
    Vec top_right = realTransform*Vec(1, 0);
    Vec bottom_right = realTransform*Vec(1, 1);
    Vec bottom_left = realTransform*Vec(0, 1);

    printf(
        "TL {%lg, %lg}, TR {%lg, %lg}, BR {%lg, %lg}, BL {%lg, %lg}\n",
        top_left.x, top_left.y,
        top_right.x, top_right.y,
        bottom_right.x, bottom_right.y,
        bottom_left.x, bottom_left.y
        );
    */
}

void Slider::handleMouseEvent(
              const MouseEvent& event,
              const math::Transform&  parent_transform)
{
  if (m_moving && event.type == MouseEvent::Type::Hold)
  {
    updateValFromMouse(event.position, parent_transform);
    return;
  }

  if (event.button != MouseEvent::Button::Left)
    return;

  if (m_moving && event.type == MouseEvent::Type::Release)
  {
    m_moving = false;
    return;
  }

  if (event.type == MouseEvent::Type::Click
      && containsPoint(event.position, parent_transform))
  {
    updateValFromMouse(event.position, parent_transform);
    m_moving = true;
    return;
  }
}

void Slider::draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform)
{
  math::Transform realTransform = parent_transform * transform();

  m_background.setRotation(realTransform.getAngleDeg());
  m_background.setPosition(realTransform.getPosition());

  math::Vec targetScale = realTransform.getScale();
  targetScale.y /= m_background.getTexture()->getSize().y;
  targetScale.x = targetScale.y;
  m_background.setScale(targetScale);

  const double handleHeight =
    m_handle.getTexture()->getSize().y * targetScale.y;

  const double offsetScale =
    (m_controller.getCurVal() - m_controller.getMinVal()) /
    (m_controller.getMaxVal() - m_controller.getMinVal());
  const math::Vec offset = offsetScale
                          * (realTransform.getScale().y - handleHeight)
                          * transform().up();

  m_handle.setRotation(realTransform.getAngleDeg());
  m_handle.setPosition(realTransform.getPosition() + offset);
  m_handle.setScale(targetScale);

  draw_target.draw(m_background);
  draw_target.draw(m_handle);
}


} // namespace ui
