/**
 * @file scene_object.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-18
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_SCENE_OBJECT_H
#define __SIMULATION_SCENE_OBJECT_H

#include "math/transform.h"
#include "simulation/movable.h"
#include "ui/render_window.h"

namespace sim
{

struct BoundingBox
{
  double xMax;
  double xMin;
  double yMax;
  double yMin;

  bool hasIntersectionWith(const BoundingBox& other) const
  {
    double x_left   = xMin > other.xMin ? xMin : other.xMin;
    double x_right  = xMax < other.xMax ? xMax : other.xMax;
    double y_bottom = yMin > other.yMin ? yMin : other.yMin;
    double y_top    = yMax < other.yMax ? yMax : other.yMax;

    return x_left < x_right && y_bottom < y_top;
  }
};

class SceneObject
{
public:
  SceneObject(math::Transform transform) : m_transform(transform) {}

  const math::Transform& transform() const { return m_transform; }
        math::Transform& transform()       { return m_transform; }

  virtual BoundingBox getBoundingBox() const = 0;

  bool intersects(const SceneObject& other) const
  {
    return getBoundingBox().hasIntersectionWith(other.getBoundingBox());
  }

  virtual void collide(SceneObject& other) const = 0;

  virtual bool isMovable() const { return false; }

  virtual Movable* asMovable() { return nullptr; }

  const Movable* asMovable() const
  {
    return const_cast<SceneObject*>(this)->asMovable();
  }

  virtual void draw(ui::RenderWindow& window) const = 0;

  virtual ~SceneObject() = default;

private:
  math::Transform m_transform;
};

} // namespace sim

#endif /* scene_object.h */
