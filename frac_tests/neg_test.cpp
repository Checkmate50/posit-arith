#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    auto f = std::make_unique<Frac>(false, 3, 5);
    auto fn = f->neg();
    std::cout << fn->as_string() << "\t" << fn->as_double() << std::endl;
    
    auto f2 = std::make_unique<Frac>(-5);
    fn = f2->neg();
    std::cout << fn->as_string() << "\t" << fn->as_double() << std::endl;
}