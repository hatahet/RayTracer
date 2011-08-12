#ifndef PPM_H_
#define PPM_H_
#pragma once

#include <string>
#include <vector>

#include "color.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

namespace raytracer {

class PpmFile {
 public:
  PpmFile(int width, int height);
  ~PpmFile();

  void SetPixel(int w, int h, const Color& c);
  Color GetPixel(int w, int h) const;
  bool WriteToFile(const std::string& filename) const;

 private:
  int width_;
  int height_;
  std::vector<Color> pixels_;

  DISALLOW_COPY_AND_ASSIGN(PpmFile);
};

inline PpmFile::PpmFile(int width, int height)
    : width_(width),
      height_(height),
      pixels_(width * height) { }

inline PpmFile::~PpmFile() { }

inline void PpmFile::SetPixel(int x, int y, const Color& c) {
  // TODO: switch to operator[]
  pixels_.at(x * width_ + y) = c;
}

inline Color PpmFile::GetPixel(int x, int y) const {
  return pixels_.at(x * width_ + y);
}

}  // namespace raytracer

#endif  // PPM_H_