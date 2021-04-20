#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Frac f(false, 4, 8);
    std::cout << f.to_string() << "\t" << f.to_double() << std::endl;
    Frac f2(-5);
    std::cout << f2.to_string() << "\t" << f2.to_double() << std::endl;
    Frac f3(3.5);
    std::cout << f3.to_string() << "\t" << f3.to_double() << std::endl;
    Frac f4(1.1);
    std::cout << f4.to_string() << "\t" << f4.to_double() << std::endl;
}