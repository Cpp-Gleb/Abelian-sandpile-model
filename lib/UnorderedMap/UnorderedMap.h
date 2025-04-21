#ifndef ARRAY2D_H
#define ARRAY2D_H

template <typename T>
class Array2D {
public:
    Array2D(int64_t width, int64_t height) : width_(width), height_(height) {
        Allocate();
    }

    ~Array2D() {
        Deallocate();
    }

    T& At(int64_t x, int64_t y) {
        return data_[x][y];
    }

    void Resize(int64_t new_width, int64_t new_height, int64_t x_shift, int64_t y_shift) {
        T** new_data = new T*[new_width];
        for (int64_t i = 0; i < new_width; ++i) {
            new_data[i] = new T[new_height]();
        }

        for (int64_t x = 0; x < width_; ++x) {
            for (int64_t y = 0; y < height_; ++y) {
                new_data[x + x_shift][y + y_shift] = data_[x][y];
            }
        }
        Deallocate();
        data_ = new_data;
        width_ = new_width;
        height_ = new_height;
    }


    int64_t GetWidth() const { return width_; }
    int64_t GetHeight() const { return height_; }

    void Set(int64_t x, int64_t y, const T& value) {
        data_[x][y] = value;
    }

    T Get(int64_t x, int64_t y) const {
        return data_[x][y];
    }

private:
    int64_t width_;
    int64_t height_;
    T** data_;

    void Allocate() {
        data_ = new T*[width_];
        for (int64_t i = 0; i < width_; ++i) {
            data_[i] = new T[height_]();
        }
    }

    void Deallocate() {
        if (data_) {
            for (int64_t i = 0; i < width_; ++i) {
                delete[] data_[i];
            }
            delete[] data_;
        }
    }
};

#endif
