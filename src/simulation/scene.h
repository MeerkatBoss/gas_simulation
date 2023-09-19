/**
 * @file scene.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_SCENE_H
#define __SIMULATION_SCENE_H

#include <cstddef>
#include "simulation/scene_object.h"
#include "simulation/reaction_builder.h"
#include "ui/render_window.h"
#include "util/linked_list.h"

namespace sim
{

class Scene
{
public:
  Scene() = default;
  Scene(const Scene& other) = delete;
  Scene& operator=(const Scene& other) = delete;

  ~Scene()
  {
    for (size_t idx = 0; idx < m_objects.getSize(); ++idx)
    {
      delete m_objects[idx];
    }
  }

  template<typename TObject>
  size_t addObject(const TObject& object)
  {
    m_objects.pushBack(new TObject(object));
    return m_objects.back()->getId();
  }

  template<typename TObject, typename... TArgs>
  size_t createObject(const TArgs&... args)
  {
    m_objects.pushBack(new TObject(args...));
    return m_objects.back()->getId();
  }

  SceneObject* findObject(size_t id);

  const SceneObject* findObject(size_t id) const
  {
    return const_cast<Scene*>(this)->findObject(id);
  }

  void drawAll(ui::RenderWindow& window) const;

  void updateObjects(double delta_time_sec);

private:

  util::DynArray<SceneObject*> m_objects;
  ReactionBuilder m_reactionBuilder;

  void moveObjects(double delta_time_sec);
  void collectDeadObjects();
  void compactObjectStorage();

};

} // namespace sim

#endif /* scene.h */
