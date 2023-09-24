/**
 * @file transform.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief Position, scale and rotation of scene object
 *
 * @version 0.1
 * @date 2023-09-11
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __RAY_TRACE_TRANSFORM_H
#define __RAY_TRACE_TRANSFORM_H

#include <cmath>
#include <math.h>
#include "math/vec.h"
#include "math/matrix.h"

namespace math
{

class Transform
{
public:
  Transform(const Point&  position  = Point(0, 0),
            const Vec&    scale     = Vec(1, 1),
            double        angle_deg = 0) :
    m_transform(
        Matrix::fromTranslation(position)*
        Matrix::fromAngle(angle_deg) *
        Matrix::fromScale(scale))
  {
  }

  Transform(const Transform& other) = default;
  Transform& operator=(const Transform& other) = default;

  Point getPosition() const
  {
    const double x = m_transform[0][2];
    const double y = m_transform[1][2];
    return Point(x, y);
  }
  void setPosition(const Point& position)
  {
    m_transform[0][2] = position.x;
    m_transform[1][2] = position.y;
  }

  Vec getScale() const
  {
    const int x_sign = m_transform[0][0] > 0 ? 1 : -1;
    const int y_sign = m_transform[1][1] > 0 ? 1 : -1;
    const double x = x_sign * hypot(m_transform[0][0], m_transform[1][0]);
    const double y = y_sign * hypot(m_transform[0][1], m_transform[1][1]);
    return Vec(x, y);
  }
  void setScale(const Vec& scale)
  {
    Vec old_scale = getScale();
    m_transform[0][0] *= scale.x / old_scale.x;
    m_transform[0][1] *= scale.x / old_scale.x;
    m_transform[1][0] *= scale.y / old_scale.y;
    m_transform[1][1] *= scale.y / old_scale.y;
  }

  double getAngleDeg() const
  {
    const Vec scale = getScale();
    return atan2(-m_transform[0][1]/scale.y, m_transform[0][0]/scale.x) * 180 / M_PI;
  }


  Vec right() const
  {
    const Vec scale = getScale();
    return Vec(m_transform[0][0]/scale.x, m_transform[1][0]/scale.x);
  }
  Vec left() const { return -right(); }

  Vec up() const
  {
    const Vec scale = getScale();
    return Vec(m_transform[0][1]/scale.y, m_transform[1][1]/scale.y);
  }
  Vec down() const { return -up(); }

  void move (const Vec& translation)
  {
    m_transform = Matrix::fromTranslation(translation) * m_transform;
  }

  void scale(const Vec& scale)
  {
    m_transform = Matrix::fromScale(scale) * m_transform;
  }

  void rotate(double angle_deg)
  {
    m_transform = Matrix::fromAngle(angle_deg) * m_transform;
  }

  Transform& operator*=(const Transform& other)
  {
    m_transform *= other.m_transform;
    return *this;
  }
  Transform operator*(const Transform& other) const
  {
    return Transform(*this)*=other;
  }

  Vec operator*(const Vec& other) const
  {
    return m_transform * other;
  }

  Transform getInverse() const
  {
    return Transform(m_transform.getInverse());
  }

private:
  Matrix m_transform;

  Transform(const Matrix& matrix) : m_transform(matrix) {}
};

} // namespace math

#endif /* transform.h */
