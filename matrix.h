#pragma once

#include "stdint.h"
#include <iostream>

constexpr uint16_t default_dimension = 4096;

struct matrix {
public:
    matrix() : matrix(default_dimension) {};
    matrix(uint16_t dimension);
    ~matrix();

    uint16_t& operator()(uint16_t row, uint16_t column);
    uint16_t& operator()(uint16_t row, uint16_t column) const;

    inline const uint16_t& get_dimension() const {
        return d;
    }

    void fill_random();

    friend std::ostream& operator<<(std::ostream& s, const matrix& m);

private:
    uint16_t d = 0;
    uint16_t** data = nullptr;
};

