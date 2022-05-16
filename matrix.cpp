#include "matrix.h"

#include <random>
#include <iostream>
#include <iomanip>      // std::setw

// #include <omp.h>

constexpr uint16_t MinNum = 1;
constexpr uint16_t MaxNum = 9;

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

void matrix::clean() {
    for (size_t i = 0; i < d; i++) {
        for (size_t j = 0; j < d; j++) {
            data[i][j] = 0;
        }
    }
}

uint16_t& matrix::operator()(uint16_t row, uint16_t column) {
    return data[row][column];
}

const uint16_t& matrix::operator()(uint16_t row, uint16_t column) const {
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
    const uint16_t& d = m.size();
    for (size_t i = 0; i < d; i++) {
        for (size_t j = 0; j < d; j++) {
            s << std::setw(2) << m(i, j) << " ";
        }
        s << "\n";
    }
    return s;
}

void stupid_multiplication(const matrix& a, const matrix& b, matrix& c) {
    // i assume they all same size
    const uint16_t n = a.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                c(i, j) += a(i, k) * b(k, j);
            }
        }
    }
}

void optimized_multiplication(const matrix& a, const matrix& b, matrix& c) {
    // i assume they all same size
    const uint16_t n = a.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t k = 0; k < n; ++k) {
            for (size_t j = 0; j < n; ++j) {
                c(i, j) += a(i, k) * b(k, j);
            }
        }
    }
}

void parallel_multiplication(const matrix& a, const matrix& b, matrix& c) {
    // i assume they all same size
    const uint16_t n = a.size();

    size_t i, j, k;

    #pragma omp parallel for private(i,j,k) shared(a,b,c)
    for (i = 0; i < n; ++i) {
        for (k = 0; k < n; ++k) {
            for (j = 0; j < n; ++j) {
                c(i, j) += a(i, k) * b(k, j);
            }
        }
    }
}

