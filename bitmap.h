#ifndef BITMAP_H_
#define BITMAP_H_
#pragma once

#include <string>
#include <vector>

#include "color.h"

namespace raytracer {

class BitmapFile {
 public:
  BitmapFile(int width, int height);
  ~BitmapFile();

  void SetPixel(int w, int h, const Color& c) { contents_[w + h * width_] = c; }
  Color GetPixel(int w, int h) const { return contents_[w + h * width_]; }
  bool WriteToFile(const std::string& filename) const;

 private:
   int width_;
   int height_;
   std::vector<Color> contents_;
};

}  // namespace raytracer
#endif  // BITMAP_H_