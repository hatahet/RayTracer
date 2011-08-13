#ifndef COLOR_H_
#define COLOR_H_
#pragma once

namespace raytracer {

// RGB ranges [0, 255].
struct Color {
  Color();
  Color(unsigned char red, unsigned char green, unsigned char blue);
  ~Color();

  unsigned char r;
  unsigned char g;
  unsigned char b;
};

inline Color::Color() : r(0), g(0), b(0) { }
inline Color::Color(unsigned char red, unsigned char green, unsigned char blue)
    : r(red), g(green), b(blue) { }
inline Color::~Color() { }


}  // namespace raytracer

#endif  // COLOR_H_
