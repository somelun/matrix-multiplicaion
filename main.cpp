#include <stdio.h>
#include "matrix.h"

int main(int argc, char* argv[]) {
    matrix m(6);
    m.fill_random();

    std::cout << m << std::endl;

    return 0;
}

