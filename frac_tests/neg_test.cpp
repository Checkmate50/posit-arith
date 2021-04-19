#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Frac f(false, 3, 5);
    auto fn = f.neg();
    std::cout << fn.as_string() << "\t" << fn.as_double() << std::endl;
    
    Frac f2(-5);
    fn = -f2;
    std::cout << fn.as_string() << "\t" << fn.as_double() << std::endl;
}