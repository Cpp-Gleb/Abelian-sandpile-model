#ifndef SANDPILE_H
#define SANDPILE_H

#include "Bmp.h"
#include "TsvReader.h"
#include "UnorderedMap.h"
#include <string>
#include <iostream>
#include <sstream>
#include <limits>

class Sandpile {
public:
    Sandpile(TsvReader& tsv, int64_t max_iteration, std::string& output_directory, int64_t frequency);

    void AddSand(int64_t x, int64_t y, uint64_t sand_count);
    void StabilizeField(int64_t max_iteration, std::string& output_directory, int64_t frequency);
    void PrintMatrix();
    uint64_t GetCellSandCount(int64_t x, int64_t y);
    void SaveToBmp(std::string& output_file);

private:
    Array2D<uint64_t> sand_map_;
    int64_t min_x_;
    int64_t min_y_;
    int64_t max_x_;
    int64_t max_y_;

    void InitializeFromFile(TsvReader& tsv, int64_t max_iteration, std::string& output_directory, int64_t frequency);
    void Check(int64_t& min_x, int64_t& max_x, int64_t& min_y, int64_t& max_y, int64_t x, int64_t y);
};

#endif
