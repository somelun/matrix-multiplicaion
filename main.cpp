#include <iostream>
#include "matrix.h"

#include "tinyclock/tinyclock.h"

constexpr uint16_t n = 2048;

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
    c.clean();

    {
        TINYCLOCK_NAME("parallel");
        parallel_multiplication(a, b, c);
    }
    c.clean();

    return 0;
}

