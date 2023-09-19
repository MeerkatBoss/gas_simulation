#include "simulation/scene.h"
#include "simulation/scene_object.h"

namespace sim
{

void Scene::drawAll(ui::RenderWindow& window) const
{
  window.renderTexture().clear(sf::Color::White);
  for (const SceneObject& object : m_objects)
  {
    object.draw(window);
  }
}

void Scene::updateObjects(double delta_time_sec)
{

}

} // namespace sim
