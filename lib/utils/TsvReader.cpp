#include "TsvReader.h"

TsvReader::TsvReader(const std::string& filepath) : filepath_(filepath) {}

bool TsvReader::ParseFile(Cell* cells, size_t& cell_count, size_t max_cells) const {
    std::ifstream file(filepath_);
    cell_count = 0;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filepath_ << std::endl;
        return false;
    }

    std::string line;
    bool is_line_first = true;
    while (std::getline(file, line) && cell_count < max_cells) {
        if (is_line_first) {
            is_line_first = false;
            continue;
        }

        std::istringstream line_stream(line);
        std::string x_str, y_str, sand_count_str;

        if (std::getline(line_stream, x_str, '\t') &&
            std::getline(line_stream, y_str, '\t') &&
            std::getline(line_stream, sand_count_str, '\t')) {

            try {
                cells[cell_count].x = static_cast<int16_t>(std::stod(x_str));
                cells[cell_count].y = static_cast<int16_t>(std::stod(y_str));
                cells[cell_count].sand_count = static_cast<uint64_t>(std::stoull(sand_count_str));
                ++cell_count;

            } catch (const std::invalid_argument& e) {
                std::cerr << "Warning: Invalid number format in line: " << line << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Warning: Number out of range in line: " << line << std::endl;
            }

        } else {
            std::cerr << "Warning: Incorrect format in line: " << line << std::endl;
        }
    }

    if (cell_count >= max_cells) {
        std::cerr << "Warning: Maximum cell capacity reached. Some cells may be omitted." << std::endl;
    }

    return true;
}

size_t TsvReader::GetRowCount() const {
    std::ifstream file(filepath_);
    size_t row_count = 0;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filepath_ << std::endl;
        return 0;
    }

    while (std::getline(file, line)) {
        ++row_count;
    }

    return row_count;
}
