#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Frac f(false, 3, 5);
    Frac f2(false, 7, 5);
    auto fn = f + f2;
    std::cout << fn.to_string() << "\t" << fn.to_double() << std::endl;
    
    Frac f3(true, 1, 3);
    Frac f4(true, 1, 2);
    fn = f3 + f4;
    std::cout << fn.to_string() << "\t" << fn.to_double() << std::endl;

    Frac f5(true, 1, 3);
    Frac f6(false, 1, 2);
    fn = f5 + f6;
    std::cout << fn.to_string() << "\t" << fn.to_double() << std::endl;

    Frac f7(false, 13, 17);
    Frac f8(true, 15, 18);
    fn = f7 - f8;
    std::cout << fn.to_string() << "\t" << fn.to_double() << std::endl;
}