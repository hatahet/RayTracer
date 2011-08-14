#ifndef VECTOR_H_
#define VECTOR_H_
#pragma once

#include <cmath>
#include <limits>

namespace raytracer {

class Vector3 {
 public:
  Vector3(double x, double y, double z);
  Vector3(const Vector3& v);
  Vector3& operator=(const Vector3& v);

  ~Vector3();

  double Dot(const Vector3& v) const;
  double Magnitude() const;
  Vector3 Cross(const Vector3& v) const;
  Vector3 Normal() const;

  friend Vector3 operator+(const Vector3& l, const Vector3& r);
  friend Vector3 operator-(const Vector3& l, const Vector3& r);
  friend Vector3 operator*(double d, const Vector3& r);
  friend bool operator==(const Vector3& l, const Vector3& r);

  double x;
  double y;
  double z;
};

inline Vector3::Vector3(double X, double Y, double Z)
    : x(X), y(Y), z(Z) { }
inline Vector3::Vector3(const Vector3& v)
    :  x(v.x), y(v.y), z(v.z) { }

inline Vector3& Vector3::operator=(const Vector3& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

inline Vector3::~Vector3() { }

inline double Vector3::Dot(const Vector3& v) const {
  return x*v.x + y*v.y + z*v.z;
}

inline double Vector3::Magnitude() const {
  return std::sqrt(Dot(*this));
}

inline Vector3 Vector3::Cross(const Vector3& v) const {
  return Vector3(y*v.z - z*v.y,
                 z*v.x - x*v.z,
                 x*v.y - y*v.x);
}

inline Vector3 Vector3::Normal() const {
  double mag = Magnitude();
  double div = mag == 0 ?
      std::numeric_limits<double>::infinity() : 1 / mag;
  return div * (*this);
}

inline Vector3 operator+(const Vector3& l, const Vector3& r) {
  return Vector3(l.x + r.x, l.y + r.y, l.z + r.z);
}

inline Vector3 operator-(const Vector3& l, const Vector3& r) {
  return Vector3(l.x - r.x, l.y - r.y, l.z - r.z);
}

inline Vector3 operator*(double d, const Vector3& v) {
  return Vector3(d * v.x, d * v.y, d * v.z);
}

inline bool operator==(const Vector3& l, const Vector3& r) {
  return l.x == r.x && l.y == r.y && l.z == r.z;
}

}

#endif  // VECTOR_H_
