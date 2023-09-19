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

  ~Scene() = default;

  template<typename TObject>
  void addObject(const TObject& object)
  {
    m_objects.pushFront(object);
  }

  template<typename TObject, typename... TArgs>
  void createObject(const TArgs&... args)
  {
    m_objects.emplaceFront<TObject>(args...);
  }


  void drawAll(ui::RenderWindow& window) const;

  void updateObjects(double delta_time_sec);

private:

  util::LinkedList<SceneObject> m_objects;
  ReactionBuilder m_reactionBuilder;

};

} // namespace sim

#endif /* scene.h */
