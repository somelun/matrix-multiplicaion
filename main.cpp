#include <iostream>
#include "matrix.h"

constexpr uint16_t n = 3;

int main(int argc, char* argv[]) {
    matrix a(n);
    a.fill_random();

    matrix b(n);
    b.fill_random();

    matrix c(n);

    stupid_multiplication(a, b, c);
    std::cout << c << std::endl;

    c.clean();

    optimized_multiplication(a, b, c);
    std::cout << c << std::endl;
    
    return 0;
}

