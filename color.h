#ifndef COLOR_H_
#define COLOR_H_
#pragma once

namespace raytracer {

struct Color {
  Color();
  Color(unsigned char red, unsigned char green, unsigned char blue);
  Color(const Color& c);

  ~Color();

  Color& operator=(const Color& c);

  unsigned char r;
  unsigned char g;
  unsigned char b;
};

inline Color::Color() : r(0), g(0), b(0) { }

inline Color::Color(unsigned char red, unsigned char green, unsigned char blue)
    : r(red), g(green), b(blue) { }

inline Color::Color(const Color& c) : r(c.r), g(c.g), b(c.b) { }

inline Color::~Color() { }

inline Color& Color::operator=(const Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    return *this;
}

}  // namespace raytracer

#endif  // COLOR_H_
