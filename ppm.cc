#include <fstream>

#include "ppm.h"

static const char* kMagic = "P6";
static const unsigned char kMaxVal = 255;

namespace raytracer {

  // http://netpbm.sourceforge.net/doc/ppm.html
  bool PpmFile::WriteToFile(const std::string& filename) const {
    if (width_ == 0 || height_ == 0)
      return false;

    std::ofstream fout(filename);
    if (!fout.is_open())
      return false;

    while (fout.good()) {
      fout << kMagic << " " << width_ << " " << height_ << " " << kMaxVal << "\n";
      for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
          Color c = GetPixel(i, j);
          fout << c.r << " " << c.g << " " << c.b << " ";
        }
        fout << "\n";
      }
    }

    return fout.good();
  }

}  // namespace raytracer
