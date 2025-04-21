#ifndef TSV_READER_H
#define TSV_READER_H

#include <string>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <iostream>

struct Cell {
    int64_t x;
    int64_t y;
    uint64_t sand_count;
};

class TsvReader {
public:
    explicit TsvReader(const std::string& filepath);

    bool ParseFile(Cell* cells, size_t& cell_count, size_t max_cells) const;
    size_t GetRowCount() const;

private:
    std::string filepath_;
};


#endif
