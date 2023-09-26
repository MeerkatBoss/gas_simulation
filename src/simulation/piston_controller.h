/**
 * @file piston_controller.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-26
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __SIMULATION_PISTON_CONTROLLER_H
#define __SIMULATION_PISTON_CONTROLLER_H

#include "simulation/wall.h"
#include "ui/slider.h"

namespace sim
{

class PistonController : public ui::SliderController
{
public:
  PistonController() :
    m_piston(nullptr),
    m_bottomPoint(),
    m_topPoint()
  {
  }

  void setPiston(Wall* piston)
  {
    m_piston = piston;
  }

  void setPistonRange(const math::Point& bottom_point,
                      const math::Point& top_point)
  {
    m_bottomPoint = bottom_point;
    m_topPoint = top_point;
  }

  virtual void onSetVal(double value) override
  {
    m_piston->transform().setPosition(
        m_bottomPoint + (m_topPoint - m_bottomPoint).normalized() * value
    );
  }

  virtual double getMaxVal() override
  {
    return (m_topPoint - m_bottomPoint).length();
  }

  virtual double getMinVal() override { return 0; }

  virtual double getCurVal() override
  {
    return (m_piston->transform().getPosition() - m_bottomPoint).length();
  }


private:
  Wall* m_piston;
  math::Point m_bottomPoint;
  math::Point m_topPoint;
};

} // namespace sim

#endif /* piston_controller.h */
