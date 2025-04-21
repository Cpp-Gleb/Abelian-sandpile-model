#include "Bmp.h"

Bmp::Bmp(int64_t width, int64_t height)
    : width_(width),
    height_(height),
    pixels_(width, height) {}

void Bmp::SetPixel(int64_t x, int64_t y, PixelColor color) {
    pixels_.Set(x, y, color);
}

PixelColor Bmp::GetPixel(int64_t x, int64_t y) {
    return pixels_.Get(x, y);
}

void Bmp::Save(const std::string& filename) {
    unsigned char fileHeader[kFileHeaderSize_] = {
        'B', 'M',
        static_cast<unsigned char>(kFileSize_),
        static_cast<unsigned char>(kFileSize_ >> kByte_),
        static_cast<unsigned char>(kFileSize_ >> kByte_ * 2),
        static_cast<unsigned char>(kFileSize_ >> kByte_ * 3),
        0, 0, 0, 0,
        static_cast<unsigned char>(kPixelArrayOffset_),
        0, 0, 0
    };

    unsigned char infoHeader[kInfoHeaderSize_] = {
        static_cast<unsigned char>(kInfoHeaderSize_), 0, 0, 0,
        static_cast<unsigned char>(width_),
        static_cast<unsigned char>(width_ >> kByte_),
        static_cast<unsigned char>(width_ >> kByte_ * 2),
        static_cast<unsigned char>(width_ >> kByte_ * 3),
        static_cast<unsigned char>(height_),
        static_cast<unsigned char>(height_ >> kByte_),
        static_cast<unsigned char>(height_ >> kByte_ * 2),
        static_cast<unsigned char>(height_ >> kByte_ * 3),
        1, 0,
        4, 0,
        0, 0, 0, 0,
        static_cast<unsigned char>(kPixelArraySize_),
        static_cast<unsigned char>(kPixelArraySize_ >> kByte_),
        static_cast<unsigned char>(kPixelArraySize_ >> kByte_ * 2),
        static_cast<unsigned char>(kPixelArraySize_ >> kByte_ * 3),
        0, 0, 0, 0,
        0, 0, 0, 0,
        16, 0, 0, 0,
        0, 0, 0, 0
    };

    const std::array<unsigned char, 64> palette = {
        255, 255, 255, 0,
        0, 128, 0, 0,
        128, 0, 128, 0,
        0, 255, 255, 0,
        0, 0, 0, 0
    };

    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        throw std::ios_base::failure("Failed to open file.");
    }

    file.write(reinterpret_cast<const char*>(fileHeader), kFileHeaderSize_);
    file.write(reinterpret_cast<const char*>(infoHeader), kInfoHeaderSize_);
    file.write(reinterpret_cast<const char*>(palette.data()), kPaletteSize_ * 4);

    for (int y = height_ - 1; y >= 0; --y) {
        for (int x = 0; x < width_; x += 2) {
            unsigned char byte = 0;
            byte |= (GetPixel(x, y) & 0x0F) << 4;
            if (x + 1 < width_) {
                byte |= (GetPixel(x + 1, y) & 0x0F);
            }
            file.put(byte);
        }
        for (int padding = 0; padding < kRowSize_ - (width_ + 1) / 2; ++padding) {
            file.put(0);
        }
    }

    file.close();
}
