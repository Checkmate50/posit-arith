#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Posit z(6, 2);
    std::cout << z.to_string() << '\t' << z.to_frac().to_string() << '\t' << z.to_double() << std::endl;

    Posit p(4, 6, 2);
    std::cout << p.to_string() << '\t' << p.to_frac().to_string() << '\t' << p.to_double() << std::endl;

    Posit p2(23, 6, 2);
    std::cout << p2.to_string() << '\t' << p2.to_frac().to_string() << '\t' << p2.to_double() << std::endl;

    Posit p3(32, 6, 2);
    std::cout << p3.to_string() << '\t' << p3.to_frac().to_string() << '\t' << p3.to_double() << std::endl;

    Posit p4(53, 6, 2);
    std::cout << p4.to_string() << '\t' << p4.to_frac().to_string() << '\t' << p4.to_double() << std::endl;
}