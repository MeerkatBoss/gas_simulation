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
#include "math/transform.h"
#include "simulation/scene_object.h"
#include "ui/canvas.h"
#include "util/dyn_array.h"

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
  TObject* addObject(const TObject& object)
  {
    return createObject<TObject>(object);
  }

  void captureObject(SceneObject* object)
  {
    m_objects.pushBack(object);
  }

  template<typename TObject, typename... TArgs>
  TObject* createObject(const TArgs&... args)
  {
    TObject* created = new TObject(args...);
    m_objects.pushBack(created);
    return created;
  }

  SceneObject* findObject(size_t id);

  const SceneObject* findObject(size_t id) const
  {
    return const_cast<Scene*>(this)->findObject(id);
  }

  void drawAll(      ui::Canvas&      window,
               const math::Transform& parent_transform) const;

  void updateObjects(double delta_time_sec);

private:
  util::DynArray<SceneObject*> m_objects;

  void tickObjects(double delta_time_sec);
  void collectDeadObjects();
  void compactObjectStorage();

};

} // namespace sim

#endif /* scene.h */
