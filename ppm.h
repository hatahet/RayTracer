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
  explicit PpmFile(int h, int w);
  ~PpmFile();

  void SetPixel(int h, int w, const Color& c);
  Color GetPixel(int h, int w) const;
  bool WriteToFile(const std::string& filename) const;

  int height() const;
  int width() const;

 private:
  int height_;
  int width_;
  std::vector<Color> pixels_;

  DISALLOW_COPY_AND_ASSIGN(PpmFile);
};

inline PpmFile::PpmFile(int h, int w)
    : height_(h),
      width_(w),
      pixels_(w * h) { }

inline PpmFile::~PpmFile() { }

inline void PpmFile::SetPixel(int x, int y, const Color& c) {
  // TODO: switch to operator[]
  pixels_.at(x * width_ + y) = c;
}

inline Color PpmFile::GetPixel(int x, int y) const {
  return pixels_.at(x * width_ + y);
}

inline int PpmFile::width() const { return width_; }
inline int PpmFile::height() const { return height_; }

}  // namespace raytracer

#endif  // PPM_H_
