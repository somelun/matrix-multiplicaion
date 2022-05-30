#include <iostream>
#include "matrix.h"

#include "tinyclock/tinyclock.h"

constexpr uint16_t n = 1024;

int main(int argc, char* argv[]) {
    matrix a(n);
    a.fill_random();
    // std::cout << a << std::endl;

    matrix b(n);
    b.fill_random();
    // std::cout << b << std::endl;

    matrix c(n);

    // std::cout << a << std::endl;
    // a.print_row_addresses();

    {
        TINYCLOCK_NAME("simple");
        simple_mult(a, b, c);
    }
    // std::cout << c << std::endl;
    c.clean();

    {
        TINYCLOCK_NAME("transposed");
        transposed_mult(a, b, c);
    }
    // std::cout << c << std::endl;
    c.clean();
    
    {
        TINYCLOCK_NAME("loopswap");
        loopswap_mult(a, b, c);
    }
    // std::cout << c << std::endl;
    // c.clean();
    // {
    //     TINYCLOCK_NAME("parallel");
    //     parallel_mult(a, b, c);
    // }
    // // std::cout << c << std::endl;
    // c.clean();

    return 0;
}

