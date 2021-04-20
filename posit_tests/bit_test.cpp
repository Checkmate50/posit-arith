#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Posit p(4, 6, 2);
    std::cout << p.signbit() << ' ' << p.regime() << ' ' << p.esbits() << ' ' << p.frbits() << std::endl;
    std::cout << p.regime_val() << ' ' << p.esbits_s() << std::endl;

    Posit p2(23, 6, 2);
    std::cout << p2.signbit() << ' ' << p2.regime() << ' ' << p2.esbits() << ' ' << p2.frbits() << std::endl;
    std::cout << p2.regime_val() << ' ' << p2.esbits_s() << std::endl;

    Posit p3(32, 6, 2);
    std::cout << p3.signbit() << ' ' << p3.regime() << ' ' << p3.esbits() << ' ' << p3.frbits() << std::endl;
    std::cout << p3.regime_val() << ' ' << p3.esbits_s() << std::endl;

    Posit p4(53, 6, 2);
    std::cout << p4.signbit() << ' ' << p4.regime() << ' ' << p4.esbits() << ' ' << p4.frbits() << std::endl;
    std::cout << p4.regime_val() << ' ' << p4.esbits_s() << std::endl;
}