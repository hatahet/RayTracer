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

  void Clamp();
  DColor GetDColor() const;

  friend Color operator+(const Color& l, const Color& r);
  friend Color operator-(const Color& l, const Color& r);
  friend Color operator*(const Color& l, const Color& r);
  friend Color operator*(double d, const Color& r);

  double r;
  double g;
  double b;

 private:
  double Clamp(double d) const;
};

inline Color::Color() : r(0.0), g(0.0), b(0.0) { }

inline Color::Color(double red, double green, double blue)
    : r(red), g(green), b(blue) {
  Clamp();
}

inline Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b) { }

inline Color& Color::operator=(const Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    return *this;
}

inline Color::~Color() { }

inline double Color::Clamp(double d) const {
  if (d > 1.0) d = 1.0;
  else if (d < 0.0) d = 0.0;
  return d;
}

inline void Color::Clamp() {
  r = Clamp(r);
  g = Clamp(g);
  b = Clamp(b);
}

inline DColor Color::GetDColor() const {
  return DColor(static_cast<unsigned char>(Clamp(r) * 255),
                static_cast<unsigned char>(Clamp(g) * 255),
                static_cast<unsigned char>(Clamp(b) * 255));
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

}  // namespace raytracer

#endif  // COLOR_H_
