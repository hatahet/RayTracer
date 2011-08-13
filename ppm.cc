#include <fstream>

#include "ppm.h"

static const char* kMagic = "P3";
static const unsigned char kMaxVal = 255;

namespace raytracer {

  // http://netpbm.sourceforge.net/doc/ppm.html
  bool PpmFile::WriteToFile(const std::string& filename) const {
    if (height_ == 0 || width_ == 0)
      return false;

    std::ofstream fout(filename + ".ppm");
    if (!fout.is_open())
      return false;

    fout << kMagic << " " << width_ << " " << height_ << " "
         << static_cast<unsigned int>(kMaxVal) << "\n";
    for (int i = 0; i < height_; ++i) {
      for (int j = 0; j < width_; ++j) {
        Color c = GetPixel(i, j);
        if (fout.good())
          fout << static_cast<unsigned int>(c.r) << " " 
               << static_cast<unsigned int>(c.g) << " " 
               << static_cast<unsigned int>(c.b) << " ";
      }
      if (fout.good())
        fout << "\n";
    }
    return fout.good();
  }

}  // namespace raytracer
