#ifndef COLOR_H_
#define COLOR_H_
#pragma once

namespace raytracer {

struct Color {
  Color() : r(0), g(0), b(0) { }
  
  Color(unsigned char red, unsigned char green, unsigned char blue)
    : r(red), g(green), b(blue) { }
  
  Color(const Color& c) : r(c.r), g(c.g), b(c.b) { }

  Color operator=(const Color& c) {
    r = c.r; g = c.g; b = c.b;
    return *this;
  }

  ~Color() { }

  unsigned char r;
  unsigned char g;
  unsigned char b;
};

}  // nmespace raytracer

#endif  // COLOR_H_