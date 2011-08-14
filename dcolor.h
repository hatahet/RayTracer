#ifndef DCOLOR_H_
#define DCOLOR_H_
#pragma once

namespace raytracer {

// RGB ranges [0, 255].
struct DColor {
  DColor(unsigned char red, unsigned char green, unsigned char blue);
  ~DColor();

  unsigned char r;
  unsigned char g;
  unsigned char b;
};

inline DColor::DColor(unsigned char red, unsigned char green, unsigned char blue)
    : r(red), g(green), b(blue) { }
inline DColor::~DColor() { }

}

#endif  // DCOLOR_H_
