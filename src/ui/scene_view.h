/**
 * @file scene_view.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-21
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_SCENE_VIEW_H
#define __SIMULATION_SCENE_VIEW_H

#include "math/vec.h"
#include "simulation/scene.h"
#include "math/transform.h"
#include "ui/canvas.h"
#include "ui/widget.h"

namespace ui
{

class SceneView : public Widget
{
public:
  SceneView(sim::Scene& scene,
            ui::Canvas* canvas,
            double pixels_per_meter,
            const math::Point& center = math::Point(),
            double angle              = 0):
    m_transform(center * pixels_per_meter,
                math::Vec(pixels_per_meter, pixels_per_meter),
                angle),
    m_scene(scene),
    m_canvas(canvas)
  {
  }

  SceneView(const SceneView& other) = delete;
  SceneView& operator=(const SceneView& other) = delete;

  ~SceneView()
  {
    delete m_canvas;
  }

  const math::Transform transform() const { return m_transform; }
        math::Transform transform()       { return m_transform; }

  void setCanvas(Canvas* canvas)
  {
    if (m_canvas != canvas)
    {
      delete m_canvas;
      m_canvas = canvas;
    }
  }

  virtual void handleMouseEvent(const MouseEvent& event) override
  {
    return m_canvas->handleMouseEvent(event);
  }

  virtual void draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform = math::Transform())
    override
  {
    sf::Vector2u texture_size = m_canvas->renderTexture().getSize();
    math::Vec scale(texture_size.x, texture_size.y);

    // math::Transform realTransform = m_transform;
    // realTransform.setScale(scale);

    m_scene.drawAll(*m_canvas, m_transform);
    
    m_canvas->draw(draw_target, parent_transform);
  }

private:
  math::Transform m_transform;
  sim::Scene&     m_scene;
  Canvas*         m_canvas;
};

} // namespace sim

#endif /* scene_view.h */
