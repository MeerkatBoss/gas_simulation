/**
 * @file plot_view.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 * 
 * @brief
 *
 * @version 0.1
 * @date 2023-09-26
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __UI_PLOT_VIEW_H
#define __UI_PLOT_VIEW_H

#include <cmath>

#include "ui/widget.h"
#include "ui/canvas.h"

namespace ui
{

class PlotView : public Widget
{
public:
  PlotView(Canvas* canvas, double unit_x, double unit_y) :
    m_canvas(canvas),
    m_recordsMax(size_t(ceil(1.0 / unit_x))),
    m_recordsCount(0),
    m_firstRecord(0),
    m_records(new Record[m_recordsMax]),
    m_unitX(unit_x),
    m_unitY(unit_y)
  {

  }

  virtual void handleMouseEvent(const MouseEvent&,
                                const math::Transform& = math::Transform())
    override
  {
    return;
  }

  virtual void draw(
                    sf::RenderTarget& draw_target,
              const math::Transform&  parent_transform = math::Transform())
    override;

  void addPoint(double delta_x, double y)
  {
    if (m_recordsCount == 0)
    {
      m_records[0] = {delta_x, y, 1};
      ++m_recordsCount;
      ++m_firstRecord;
      return;
    }

    size_t new_idx = (m_firstRecord + m_recordsCount) % m_recordsMax;
    size_t last_idx = (m_firstRecord + m_recordsCount - 1) % m_recordsMax;

    double new_delta = m_records[last_idx].delta_x + delta_x;
    if (new_delta < m_unitX)
    {
      m_records[last_idx].delta_x = new_delta;
      m_records[last_idx].y =
        (m_records[last_idx].y*m_records[last_idx].count + y) /
        (m_records[last_idx].count + 1);
      ++m_records[last_idx].count;
      return;
    }

    if (new_idx != m_firstRecord)
    {
      ++m_recordsCount;
    }
      
    m_records[new_idx] = {
      delta_x,
      y,
      1
    };

    m_firstRecord = (m_firstRecord + 1) % m_recordsMax;
  }

  ~PlotView() override
  {
    delete m_canvas;
    delete[] m_records;
  }
    
private:
  struct Record
  {
    double delta_x, y;
    size_t count;
  };

  Canvas* m_canvas;

  size_t  m_recordsMax;
  size_t  m_recordsCount;
  size_t  m_firstRecord;
  Record* m_records;

  double  m_unitX;
  double  m_unitY;
};

} // namespace ui

#endif /* plot_view.h */
