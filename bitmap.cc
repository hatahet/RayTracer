#include <cstdint>

#include "bitmap.h"

namespace {
  // The magic number is separate from the BitmapFileheader struct as it
  // causes alignment issues.  BitmapMagic should be read/written first
  // followed by BitmapFileHeader.
  struct BitmapMagic {
    unsigned char magic[2];
  };

  struct BitmapFileHeader {
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bmp_offset;
  };
}  // namespace

namespace raytracer {

BitmapFile::BitmapFile(int width, int height)
    : width_(width),
      height_(height), 
      contents_(width * height) { }

BitmapFile::~BitmapFile() {
  contents_.clear();  // Probably no need to do this.
}

bool BitmapFile::WriteToFile(const std::string& filename) const {
  // Open file, if failed return false;

  BitmapMagic bitmap_magic;
  BitmapFileHeader bitmap_file_header;
  return true;
}

}  // namespace raytracer
