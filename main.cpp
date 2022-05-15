#include <iostream>
#include "matrix.h"

#include "tinyclock/tinyclock.h"

constexpr uint16_t n = 32;

int main(int argc, char* argv[]) {
    matrix a(n);
    a.fill_random();

    matrix b(n);
    b.fill_random();

    matrix c(n);

    {
        TINYCLOCK_NAME("normal");
        stupid_multiplication(a, b, c);
    }

    c.clean();

    {
        TINYCLOCK_NAME("optimized");
        optimized_multiplication(a, b, c);
    }

    return 0;
}

// TODO: try to use advice from https://stackoverflow.com/questions/48527189/is-there-a-way-to-flush-the-entire-cpu-cache-related-to-a-program
