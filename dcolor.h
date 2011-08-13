#ifndef DCOLOR_H_
#define DCOLOR_H_
#pragma once

#include "color.h"

namespace raytracer {

// RGB ranges [0, 1.0].
class DColor {
 public:
  DColor(double red, double green, double blue);
  DColor(const Color& c);
  DColor& operator=(const DColor& c);

  ~DColor();

  Color GetColor() const;

  friend DColor operator+(const DColor& l, const DColor& r);
  friend DColor operator-(const DColor& l, const DColor& r);
  friend DColor operator*(const DColor& l, const DColor& r);
  friend DColor operator*(double d, const DColor& r);

  double r;
  double g;
  double b;

 private:
  double Normalize(double d) const;
};

inline DColor::DColor(double red, double green, double blue)
    : r(red), g(green), b(blue) { }

inline DColor::DColor(const Color& c) : r(c.r), g(c.g), b(c.b) { }

inline DColor::~DColor() { }

inline DColor& DColor::operator=(const DColor& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    return *this;
}

inline Color DColor::GetColor() const {
  return Color(static_cast<unsigned char>(Normalize(r) * 255),
               static_cast<unsigned char>(Normalize(g) * 255),
               static_cast<unsigned char>(Normalize(b) * 255));
}

inline DColor operator+(const DColor& l, const DColor& r) {
  return DColor(l.r + r.r, l.g + r.g, l.b + r.b);
}

inline DColor operator-(const DColor& l, const DColor& r) {
  return DColor(l.r - r.r, l.g - r.g, l.b - r.b);
}

inline DColor operator*(const DColor& l, const DColor& r) {
  return DColor(l.r * r.r, l.g * r.g, l.b * r.b);
}

inline DColor operator*(double d, const DColor& r) {
  return DColor(d * r.r, d * r.g, d * r.b);
}

inline double Normalize(double d) {
  // XXX: Check for -ve?
  return (d < 1.0) ? d : 1.0;
}

}

#endif  // DCOLOR_H_
