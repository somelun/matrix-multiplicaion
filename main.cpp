#include <iostream>
#include "matrix.h"

#include "tinyclock/tinyclock.h"

constexpr uint16_t n = 4;

int main(int argc, char* argv[]) {
    matrix a(n);
    a.fill_random();

    matrix b(n);
    b.fill_random();

    matrix c(n);

    {
        TINYCLOCK_NAME("simple");
        simple_mult(a, b, c);
    }
    // std::cout << c << std::endl;
    c.clean();

    // {
    //     TINYCLOCK_NAME("transposed");
    //     transposed_mult(a, b, c);
    // }
    // std::cout << c << std::endl;
    // c.clean();

    {
        TINYCLOCK_NAME("loopswap");
        loopswap_mult(a, b, c);
    }
    // std::cout << c << std::endl;
    c.clean();

    // {
    //     TINYCLOCK_NAME("parallel");
    //     parallel_mult(a, b, c);
    // }
    // c.clean();

    return 0;
}

