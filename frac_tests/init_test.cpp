#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Frac f(false, 3, 5);
    std::cout << f.as_string() << "\t" << f.as_double() << std::endl;
    Frac f2(-5);
    std::cout << f2.as_string() << "\t" << f2.as_double() << std::endl;
    Frac f3(3.5);
    std::cout << f3.as_string() << "\t" << f3.as_double() << std::endl;
    Frac f4(1.1);
    std::cout << f4.as_string() << "\t" << f4.as_double() << std::endl;
}