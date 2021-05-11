#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Frac f(false, 3, 5);
    Frac f2(false, 7, 5);
    std::cout << (f == f2) << "\t" << (f <= f2) << std::endl;
    
    Frac f3(true, 1, 2);
    Frac f4(true, 1, 3);
    std::cout << (f3 == f4) << "\t" << (f3 < f4) << std::endl;

    Frac f5(true, 1, 3);
    Frac f6(false, 1, 3);
    std::cout << (f5 == f6) << "\t" << (f5 > f6) << std::endl;

    Frac f7(false, 13, 17);
    Frac f8(true, 15, 18);
    std::cout << (f7 < f8) << "\t" << (f7 >= f8) << std::endl;
}