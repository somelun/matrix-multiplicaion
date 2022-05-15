#pragma once

#include "stdint.h"
#include <iostream>

constexpr uint16_t default_dimension = 4096;

struct matrix {
public:
    matrix() : matrix(default_dimension) {};
    matrix(uint16_t dimension);
    ~matrix();

    void clean();

    uint16_t& operator()(uint16_t row, uint16_t column);
    const uint16_t& operator()(uint16_t row, uint16_t column) const;

    inline const uint16_t& size() const {
        return d;
    }

    void fill_random();

    friend std::ostream& operator<<(std::ostream& s, const matrix& m);

private:
    uint16_t d = 0;
    uint16_t** data = nullptr;
};

void stupid_multiplication(const matrix& a, const matrix& b, matrix& c);
void optimized_multiplication(const matrix& a, const matrix& b, matrix& c);

