#pragma once

#include "stdint.h"
#include <iostream>

constexpr uint16_t default_dimension = 4096;

#define CONTIGOUS

struct matrix {
public:
    matrix() : matrix(default_dimension) {};
    matrix(uint16_t dimension);
    ~matrix();

    void clean();

    uint16_t& operator()(uint16_t row, uint16_t column);
    const uint16_t& operator()(uint16_t row, uint16_t column) const;

    inline const uint16_t size() const {
#ifdef CONTIGOUS
        return d * d;
#else
        return d;
#endif
    }

    void fill_random();

    // since I use [N][N] and not [N * N] matrix allocation, I want to see memory alignment
    // for the elements, so I print address for every first element in the row. I know how
    // many elements in every row (N) so I can say if memory is continguous or not.
    void print_row_addresses() const;

    friend std::ostream& operator<<(std::ostream& s, const matrix& m);

private:
    // if CONTIGOUS then all elements in array will be d * d
    uint16_t d = 0;

#ifdef CONTIGOUS
    uint16_t* data = nullptr;
#else
    uint16_t** data = nullptr;
#endif
};

void transpose(const matrix& a, matrix& m);

void simple_mult(const matrix& a, const matrix& b, matrix& c);
void transposed_mult(const matrix& a, const matrix& b, matrix& c);
void loopswap_mult(const matrix& a, const matrix& b, matrix& c);
void parallel_mult(const matrix& a, const matrix& b, matrix& c);

