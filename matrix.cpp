#include "matrix.h"

#include <random>
#include <iostream>
#include <iomanip>      // std::setw

#include <omp.h>

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
    for (size_t i = 0; i < d; ++i) {
        for (size_t j = 0; j < d; ++j) {
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

void transpose(const matrix& a, matrix& m) {
    const uint16_t& d = a.size();

    for (size_t i = 0; i < d; i++) {
        for (size_t j = 0; j < d; j++) {
            m(j, i) = a(i, j);
        }
    }
}

void simple_mult(const matrix& a, const matrix& b, matrix& c) {
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

// TODO: all inside is work im progress
void transposed_mult(const matrix& a, const matrix& b, matrix& c) {
    // i assume they all same size
    const uint16_t n = a.size();

    matrix bt(n);
    transpose(b, bt);

    matrix ct(n);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            float x = 0.0f;
            for (size_t k = 0; k < n; ++k) {
                x += a(i, k) * b(j, k);
            }
            c(i, j) = x;
        }
    }

    // transpose(ct, c);
}

void loopswap_mult(const matrix& a, const matrix& b, matrix& c) {
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

void parallel_mult(const matrix& a, const matrix& b, matrix& c) {
    // i assume they all same size
    const uint16_t n = a.size();

    size_t i, j, k;

    #pragma omp parallel //for private(i, j, k) shared(a,b,c)
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            for (k = 0; k < n; ++k) {
                c(i, j) += a(i, k) * b(k, j);
            }
        }
    }
}



// transpose test
// 1 2 3     1 4 7
// 4 5 6     2 5 6
// 7 8 9     3 6 9

// consider this https://en.wikipedia.org/wiki/Strassen_algorithm
