#include "simulation/scene.h"
#include <cstddef>
#include "simulation/movable.h"
#include "simulation/scene_object.h"

namespace sim
{

SceneObject* Scene::findObject(size_t id)
{
  for (size_t idx = 0; idx < m_objects.getSize(); ++idx)
  {
    if (m_objects[idx]->getId() == id)
      return m_objects[idx];
  }

  return nullptr;
}

void Scene::drawAll(ui::RenderWindow& window) const
{
  window.renderTexture().clear(sf::Color::White);
  for (size_t idx = 0; idx < m_objects.getSize(); ++idx)
  {
    m_objects[idx]->draw(window);
  }
}

void Scene::updateObjects(double delta_time_sec)
{
  moveObjects(delta_time_sec);
  collectDeadObjects();
}

void Scene::moveObjects(double delta_time_sec)
{
  for (size_t idx = 0; idx < m_objects.getSize(); ++idx)
  {
    if (!m_objects[idx]->isMovable())
    {
      continue;
    }

    Movable* movable = m_objects[idx]->asMovable();
    m_objects[idx]->transform().move(movable->velocity() * delta_time_sec);
  }
}

void Scene::collectDeadObjects()
{
  for (size_t idx = 0; idx < m_objects.getSize(); ++idx)
  {
    if (m_objects[idx]->isDead())
    {
      delete m_objects[idx];
      m_objects[idx] = nullptr;
    }
  }

  compactObjectStorage();
}

void Scene::compactObjectStorage()
{
  size_t idx = 0;
  
  while (idx < m_objects.getSize())
  {
    // Find last non-null
    while (!m_objects.isEmpty() && m_objects.back() == nullptr)
    {
      m_objects.popBack();
    }

    if (idx > m_objects.getSize())
    {
      break;
    }

    // Find first null
    while (idx < m_objects.getSize() && m_objects[idx] != nullptr)
    {
      ++ idx;
    }

    // If found null
    if (idx < m_objects.getSize())
    {
      m_objects[idx] = m_objects.back();
      m_objects.popBack();
    }
  }
}

} // namespace sim
