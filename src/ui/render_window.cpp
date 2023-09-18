#include "ui/render_window.h"
#include <SFML/Graphics/Sprite.hpp>
#include "math/transform.h"

namespace ui
{

void RenderWindow::draw(      sf::RenderTarget& draw_target,
                        const math::Transform&  parent_transform)
{
  math::Transform realTransform = transform()*parent_transform;

  sf::Sprite sprite(m_renderTexture.getTexture());
  sprite.setRotation(realTransform.getAngleDeg());
  sprite.setPosition(realTransform.getPosition());

  math::Vec targetScale = realTransform.getScale();
  targetScale.x /= renderTexture().getSize().x;
  targetScale.y /= renderTexture().getSize().y;
  sprite.setScale(targetScale);
  
  draw_target.draw(sprite);
}

} // namespace ui
