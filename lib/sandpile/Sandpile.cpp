#include "Sandpile.h"


Sandpile::Sandpile(TsvReader& tsv, int64_t max_iteration, std::string& output_directory, int64_t frequency)
    : sand_map_(1, 1),
      min_x_(std::numeric_limits<int64_t>::max()),
      min_y_(std::numeric_limits<int64_t>::max()),
      max_x_(std::numeric_limits<int64_t>::min()),
      max_y_(std::numeric_limits<int64_t>::min()) {
    size_t cell_count = tsv.GetRowCount();
    Cell* cells = new Cell[cell_count];
    if (!tsv.ParseFile(cells, cell_count, cell_count + 1)) {
        delete[] cells;
        throw std::runtime_error("Ошибка при парсинге TSV файла");
    }

    for (size_t i = 0; i < cell_count; ++i) {
        int64_t x = cells[i].x;
        int64_t y = cells[i].y;
        min_x_ = std::min(min_x_, x);
        max_x_ = std::max(max_x_, x);
        min_y_ = std::min(min_y_, y);
        max_y_ = std::max(max_y_, y);
    }

    int64_t width = max_x_ - min_x_ + 1;
    int64_t height = max_y_ - min_y_ + 1;
    sand_map_.Resize(width, height, 0, 0);
    for (size_t i = 0; i < cell_count; ++i) {
        int64_t x = cells[i].x;
        int64_t y = cells[i].y;
        sand_map_.At(x - min_x_, y - min_y_) = cells[i].sand_count;
    }

    delete[] cells;
    StabilizeField(max_iteration, output_directory, frequency);
}

void Sandpile::PrintMatrix() {
    for (int64_t y = 0; y <= max_y_ - min_y_; ++y) {
        for (int64_t x = 0; x <= max_x_ - min_x_; ++x) {
            std::cout << sand_map_.At(x, y) << " ";
        }
        std::cout << "\n";
    }
}

void Sandpile::AddSand(int64_t x, int64_t y, uint64_t sand_count) {
    sand_map_.At(x, y) += sand_count;
}

void Sandpile::StabilizeField(int64_t max_iteration, std::string& output_directory, int64_t frequency) {
    int64_t iteration_count = 0;
    const int64_t kOverflowCriterion = 4;
    bool is_not_stable = true;
    int64_t height = max_y_ - min_y_ + 1;
    int64_t width = max_x_ - min_x_ + 1;
    while (is_not_stable) {
        is_not_stable = false;
        for (int64_t x = 0; x < width; ++x) {
            for (int64_t y = 0; y < height; ++y) {
                if (sand_map_.At(x, y) >= kOverflowCriterion) {
                    is_not_stable = true;
                    if(x + 1 >= width) sand_map_.Resize(++width, height, 0, 0);
                    if(y + 1 >= height) sand_map_.Resize(width, ++height, 0, 0);
                    if(x - 1 < 0) sand_map_.Resize(++width, height, 1, 0);
                    if(x - 1 < 0) sand_map_.Resize(width, ++height, 0, 1);
                    if (sand_map_.At(x, y) >= kOverflowCriterion) {
                        sand_map_.At(x + 1, y) += 1;
                        sand_map_.At(x - 1, y) += 1;
                        sand_map_.At(x, y + 1) += 1;
                        sand_map_.At(x, y - 1) += 1;
                        sand_map_.At(x, y) -= 4;
                    }
                }
            }
        }

        if (frequency == 1) {
            std::stringstream filename;
            filename << output_directory << "/" << iteration_count << ".bmp";
            std::string filename_str = filename.str();
            SaveToBmp(filename_str);
        }

        iteration_count++;

        if(iteration_count == max_iteration) {
            break;
        }
    }

    if (frequency == 0) {
        std::stringstream filename;
        filename << output_directory << "/" << iteration_count << ".bmp";
        std::string filename_str = filename.str();
        SaveToBmp(filename_str);
    }
}

uint64_t Sandpile::GetCellSandCount(int64_t x, int64_t y) {
    return sand_map_.At(x - min_x_, y - min_y_);
}


void Sandpile::SaveToBmp(std::string& output_file) {
    int64_t height = sand_map_.GetHeight();
    int64_t width = sand_map_.GetWidth();
    Bmp bmp(width, height);

    for (int64_t x = 0; x < width; ++x) {
        for (int64_t y = 0; y < height; ++y) {
            uint64_t sand_count = sand_map_.At(x, y);
            if (sand_count == kWhitePixel) {
                bmp.SetPixel(x, y, kWhitePixel);
            } else if (sand_count == kGreenPixel) {
                bmp.SetPixel(x, y, kGreenPixel);
            } else if (sand_count == kPurplePixel) {
                bmp.SetPixel(x, y, kPurplePixel);
            } else if (sand_count == kYellowPixel) {
                bmp.SetPixel(x, y, kYellowPixel);
            } else {
                bmp.SetPixel(x, y, kBlackPixel);
            }
        }
    }

    bmp.Save(output_file);
    std::cout << "BMP file saved: " << output_file << '\n';
}
