/**
 * @file wall.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-22
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_WALL_H
#define __SIMULATION_WALL_H

#include "math/transform.h"
#include "simulation/scene_object.h"

namespace sim
{

class Wall : public SceneObject
{
public:
  Wall(const math::Point& pos, double len, double angle = 0) :
    SceneObject(math::Transform(pos, math::Vec(len, .05*len), angle))
  {
  }

  BoundingBox getBoundingBox() const override;

  void collide(SceneObject& other) override;

  void draw(ui::Canvas& window, const math::Transform& parent_transform)
    const override;
};

} // namespace sim

#endif /* wall.h */
