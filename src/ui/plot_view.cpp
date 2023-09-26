#include "ui/plot_view.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

namespace ui
{

void PlotView::draw(sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform)
{
  m_canvas->renderTexture().clear(sf::Color::White);

  const size_t unit_x_px = m_canvas->renderTexture().getSize().x;
  const size_t unit_y_px = m_canvas->renderTexture().getSize().y * m_unitY;

  if (m_recordsCount > 0)
  {
    sf::VertexArray vertex_array(sf::TriangleStrip, 2*m_recordsCount);
    double x = 0;
    for (size_t i = 0; i < m_recordsCount; ++i)
    {
      size_t idx = (m_firstRecord + i) % m_recordsMax;

      vertex_array[2*i].position = sf::Vector2f(
        x * unit_x_px,
        m_records[idx].y * unit_y_px
      );
      vertex_array[2*i].color = sf::Color::Red;

      vertex_array[2*i + 1].position = sf::Vector2f(
        x * unit_x_px + 15,
        m_records[idx].y * unit_y_px - 15
      );
      vertex_array[2*i + 1].color = sf::Color::Red;

      x += m_records[idx].delta_x;
    }
    m_canvas->renderTexture().draw(vertex_array);
  }

  m_canvas->draw(draw_target, parent_transform);
}

} // namespace sim
