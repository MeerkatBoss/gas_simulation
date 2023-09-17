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
  sprite.setScale   (realTransform.getScale());
  
  draw_target.draw(sprite);
}

} // namespace ui
