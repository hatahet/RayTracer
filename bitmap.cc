#include <cstdint>

#include "bitmap.h"

namespace {
  // The magic number is separate from the BitmapFileheader struct as it
  // causes alignment issues.  BitmapMagic should be read/written first
  // followed by BitmapFileHeader.
  struct BitmapMagic {
    static const unsigned char magic[2];
  };

  const unsigned char BitmapMagic::magic[] = {'B', 'M'};

  struct BitmapFileHeader {
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bmp_offset;
  };

  struct BitmapInfoHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t num_color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression_method;
    uint32_t image_size;
    int32_t horizontal_resolution;
    int32_t vertical_resolution;
    uint32_t num_colors;
    uint32_t num_important_colors;
  };

  const int kPixelSize = 4;  // (r, g, b, unused).

  template <typename T>
  inline bool WriteBytes(/* file */ const T& data) {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&data);
    for (decltype(sizeof(T)) i = 0; i < sizeof(T); ++i) {
      /*Write(*/*p++/*)*/;
    }
    return true;
  }
}  // namespace

namespace raytracer {

bool BitmapFile::WriteToFile(const std::string& filename) const {
  // Open file, if failed return false;
  // contents_.reserve((width_ + padding) * height_);

  if (width_ == 0 || height_ == 0)
    return false;

  BitmapMagic bitmap_magic;

  // Must be zero-padded to end of 32-bit (4-byte) boundary.
  const int padding = (width_ % 4) == 0 ? 0 : 4 - (width_ % 4);
  const int actual_width = width_ + padding;
  BitmapFileHeader bitmap_file_header = {
    actual_width * height_ * kPixelSize,
    0, 0
  };

  for (int i = 0; i < actual_width; ++i) {
    if (i >= width_) {
      // write 0
      WriteBytes(0);
      continue;
    }
  }
  return true;
}

}  // namespace raytracer
