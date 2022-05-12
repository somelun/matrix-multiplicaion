#include "matrix.h"

#include <random>
#include <iostream>
#include <iomanip>      // std::setw

constexpr uint16_t MinNum = 1;
constexpr uint16_t MaxNum = 99;

matrix::matrix(uint16_t dimension) : d(dimension) {
    data = new uint16_t* [d];
    for (uint16_t i = 0; i < d; ++i) {
        data[i] = new uint16_t[d];
    }
}

matrix::~matrix() {
    for (uint16_t i = 0; i < d; ++i) {
        delete [] data[i];
    }
    delete [] data;
}

uint16_t& matrix::operator()(uint16_t row, uint16_t column) {
    return data[row][column];
}
uint16_t& matrix::operator()(uint16_t row, uint16_t column) const {
    return data[row][column];
}

void matrix::fill_random() {
    std::random_device rd;
    // std::default_random_engine eng(rd());
    std::mt19937 eng(rd());
    std::uniform_int_distribution<uint16_t> distr(MinNum, MaxNum);

    for (size_t i = 0; i < d; i++) {
        for (size_t j = 0; j < d; j++) {
            data[i][j] = distr(eng);
        }
    }
}

std::ostream& operator<<(std::ostream& s, const matrix& m) {
    const uint16_t& d = m.get_dimension();
    for (size_t i = 0; i < d; i++) {
        for (size_t j = 0; j < d; j++) {
            s << std::setw(2) << m(i, j) << " ";
        }
        s << "\n";
    }
    return s;
}

