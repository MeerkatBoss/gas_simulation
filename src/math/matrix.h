/**
 * @file matrix.h
 * @author MeerkatBoss (solodovnikov.ia@phystech.edu)
 *
 * @brief 3x3 matrix for vector transformations
 *
 * @version 0.1
 * @date 2023-09-11
 *
 * @copyright Copyright MeerkatBoss (c) 2023
 */
#ifndef __RAY_TRACE_MATRIX_H
#define __RAY_TRACE_MATRIX_H

#include <cmath>
#include <cstddef>

#include "math/vec.h"

namespace math
{

class Matrix
{
public:
  static const Matrix One;

  Matrix() :
    m_coords{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
  {
  }
  Matrix(const double (&matrix)[3][3])
  {
    for (size_t i = 0; i < 3; ++i)
      for (size_t j = 0; j < 3; ++j)
        m_coords[i][j] = matrix[i][j];
  }
  Matrix(const Matrix& other) = default;
  Matrix& operator=(const Matrix& other) = default;

  static Matrix fromAngle(double angle_deg)
  {
    const double angle = angle_deg / 180 * M_PI;
    const double cos_a = cos(angle);
    const double sin_a = sin(angle);

    return Matrix({
        { cos_a, -sin_a, 0},
        { sin_a,  cos_a, 0},
        {     0,      0, 1}
    });
  }

  static Matrix fromScale(const Vec& scale)
  {
    return Matrix({
        { scale.x, 0,         0 },
        { 0,         scale.y, 0 },
        { 0,         0,       1 }
    });
  }

  static Matrix fromTranslation(const Vec& translation)
  {
    return Matrix({
        { 1, 0, translation.x },
        { 0, 1, translation.y },
        { 0, 0,               1 }
    });
  }

  typedef       double (&     Row)[3];
  typedef const double (&ConstRow)[3];

  ConstRow operator[](size_t index) const { return m_coords[index]; }
       Row operator[](size_t index)       { return m_coords[index]; }

  Matrix& operator*=(const Matrix& other)
  {
    for (size_t i = 0; i < 3; ++i)
    {
      double row[3] = { 0, 0, 0 };
      for (size_t j = 0; j < 3; ++j)
        for (size_t k = 0; k < 3; ++k)
          row[j] += m_coords[i][k] * other[k][j];

      for (size_t j = 0; j < 3; ++j)
        m_coords[i][j] = row[j];
    }
    return *this;
  }

  Matrix& operator*=(double scale)
  {
    for (size_t i = 0; i < 3; ++i)
      for (size_t j = 0; j < 3; ++j)
        m_coords[i][j] *= scale;

    return *this;
  }

  Matrix& operator+=(const Matrix& other)
  {
    for (size_t i = 0; i < 3; ++i)
      for (size_t j = 0; j < 3; ++j)
        m_coords[i][j] += other[i][j];
    return *this;
  }

  Matrix& operator-=(const Matrix& other)
  {
    for (size_t i = 0; i < 3; ++i)
      for (size_t j = 0; j < 3; ++j)
        m_coords[i][j] -= other[i][j];
    return *this;
  }

  Matrix operator*(const Matrix& other) const { return Matrix(*this) *= other; }
  Matrix operator*(double scale)        const { return Matrix(*this) *= scale; }
  Matrix operator+(const Matrix& other) const { return Matrix(*this) += other; }
  Matrix operator-(const Matrix& other) const { return Matrix(*this) -= other; }
  Matrix operator-()                    const { return Matrix(*this) *= -1; }

  double determinant() const
  {
    return m_coords[0][0]*m_coords[1][1]*m_coords[2][2]
         + m_coords[0][1]*m_coords[1][2]*m_coords[2][0]
         + m_coords[0][2]*m_coords[1][0]*m_coords[2][1]
         - m_coords[0][2]*m_coords[1][1]*m_coords[2][0]
         - m_coords[0][1]*m_coords[1][0]*m_coords[2][2]
         - m_coords[0][0]*m_coords[1][2]*m_coords[2][1];
  }

  bool hasInverse() const
  {
    return fabs(determinant()) >= EPS;
  }

  Vec operator*(const Vec& vec) const
  {
    const Vec row_x(m_coords[0][0], m_coords[0][1]);
    const Vec row_y(m_coords[1][0], m_coords[1][1]);
    const Vec row_z(m_coords[2][0], m_coords[2][1]);

    const double new_x = Vec::dotProduct(row_x, vec) + m_coords[0][2];
    const double new_y = Vec::dotProduct(row_y, vec) + m_coords[1][2];
    const double new_z = Vec::dotProduct(row_z, vec) + m_coords[2][2];

    if (fabs(new_z) < EPS)
    {
      return Vec(NAN, NAN);
    }

    return Vec(new_x / new_z, new_y / new_z);
  }

  Matrix getInverse() const
  {
    if (!hasInverse())
      return Matrix();

    return Matrix({{getAdjunct(0, 0), getAdjunct(0, 1), getAdjunct(0, 2)},
                   {getAdjunct(1, 0), getAdjunct(1, 1), getAdjunct(1, 2)},
                   {getAdjunct(2, 0), getAdjunct(2, 1), getAdjunct(2, 2)}}) *=
           1.0 / determinant();
  }

private:
  static double constexpr EPS = 1e-6;
  double m_coords[3][3];

  double getAdjunct(size_t i, size_t j) const { return getCofactor(j, i); }

  double getCofactor(size_t i, size_t j) const
  {
    const int sign = (i + j) % 2 == 0 ? 1 : -1;

    size_t i0 = i == 0 ? 1 : 0;
    size_t j0 = j == 0 ? 1 : 0;
    size_t i1 = i == 1 || i0 == 1 ? 2 : 1;
    size_t j1 = j == 1 || j0 == 1 ? 2 : 1;

    return sign * ( m_coords[i0][j0]*m_coords[i1][j1]
                  - m_coords[i0][j1]*m_coords[i1][j0] );
  }
};

inline Matrix operator*(double scale, const Matrix& matrix)
{
  return matrix * scale;
}

} // namespace math


#endif /* matrix.h */
