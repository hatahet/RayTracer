#ifndef COLOR_H_
#define COLOR_H_
#pragma once

#include "dcolor.h"

namespace raytracer {

// RGB ranges [0, 1.0].
class Color {
 public:
  Color();
  Color(double red, double green, double blue);
  Color(const Color& c);
  Color& operator=(const Color& c);

  ~Color();

  DColor GetDColor() const;

  friend Color operator+(const Color& l, const Color& r);
  friend Color operator-(const Color& l, const Color& r);
  friend Color operator*(const Color& l, const Color& r);
  friend Color operator*(double d, const Color& r);

  double r;
  double g;
  double b;

 private:
  double Legalize(double d) const;
};

inline Color::Color() : r(0.0), g(0.0), b(0.0) { }

inline Color::Color(double red, double green, double blue)
    : r(red), g(green), b(blue) { }

inline Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b) { }

inline Color& Color::operator=(const Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    return *this;
}

inline Color::~Color() { }

inline DColor Color::GetDColor() const {
  return DColor(static_cast<unsigned char>(Legalize(r) * 255),
                static_cast<unsigned char>(Legalize(g) * 255),
                static_cast<unsigned char>(Legalize(b) * 255));
}

inline Color operator+(const Color& l, const Color& r) {
  return Color(l.r + r.r, l.g + r.g, l.b + r.b);
}

inline Color operator-(const Color& l, const Color& r) {
  return Color(l.r - r.r, l.g - r.g, l.b - r.b);
}

inline Color operator*(const Color& l, const Color& r) {
  return Color(l.r * r.r, l.g * r.g, l.b * r.b);
}

inline Color operator*(double d, const Color& r) {
  return Color(d * r.r, d * r.g, d * r.b);
}

inline double Color::Legalize(double d) const {
  // XXX: Check for -ve?
  return (d < 1.0) ? d : 1.0;
}

}  // namespace raytracer

#endif  // COLOR_H_
