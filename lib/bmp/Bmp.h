#ifndef BMP_H
#define BMP_H

#include <array>
#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include "UnorderedMap.h"

enum PixelColor {
    kWhitePixel = 0,
    kGreenPixel = 1,
    kPurplePixel = 2,
    kYellowPixel = 3,
    kBlackPixel = 4
};

class Bmp {
public:
    Bmp(int64_t width, int64_t height);

    PixelColor GetPixel(int64_t x, int64_t y);
    void SetPixel(int64_t x, int64_t y, PixelColor color);
    void Save(const std::string& filename);

private:
    int64_t width_;
    int64_t height_;
    Array2D<PixelColor> pixels_;

    const int kByte_ = 8;
    const int kFileHeaderSize_ = 14;
    const int kInfoHeaderSize_ = 40;
    const int kPaletteSize_ = 16;
    const int kPixelArrayOffset_ = kFileHeaderSize_ + kInfoHeaderSize_ + kPaletteSize_ * 4;

    const int kRowSize_ = ((width_ + 1) / 2 + 3) & ~3;
    const int kPixelArraySize_ = kRowSize_ * height_;
    const int kFileSize_ = kPixelArrayOffset_ + kPixelArraySize_;
};

#endif
