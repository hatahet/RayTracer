#ifndef BITMAP_H_
#define BITMAP_H_
#pragma once

#include <string>
#include <vector>

#include "color.h"

namespace raytracer {

// TODO: Make an Image abstract class/interface
class BitmapFile {
 public:
  BitmapFile(int width, int height);
  ~BitmapFile();

  void SetPixel(int w, int h, const Color& c);
  Color GetPixel(int w, int h) const;
  bool WriteToFile(const std::string& filename) const;

 private:
   int width_;
   int height_;
   std::vector<Color> contents_;
};

inline BitmapFile::BitmapFile(int width, int height)
    : width_(width),
      height_(height),
      contents_(width * height) { }

inline BitmapFile::~BitmapFile() { }

inline void BitmapFile::SetPixel(int x, int y, const Color& c) {
  contents_.at(x * width_ + y) = c;
}

inline Color BitmapFile::GetPixel(int x, int y) const {
  return contents_.at(x * width_ + y);
}


}  // namespace raytracer

#endif  // BITMAP_H_
