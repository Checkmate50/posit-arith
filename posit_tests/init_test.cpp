#include "../src/posit.hpp"
#include "../src/frac.hpp"
#include <iostream>

int main() {
    Posit p;
    std::cout << p.is_zero() << ' ' << p.is_neg() << ' ' << p.is_equal(Posit()) << std::endl;
    Posit p2(8, 2);
    std::cout << p2.is_zero() << ' ' << p2.is_inf() << ' ' << p2.is_equal(p) << std::endl;
    Posit p3(static_cast<uint64_t>(2147483663)); // 1000...001111, 32 bits total
    std::cout << p3.is_zero() << ' ' << p3.is_neg() << ' ' << p2.is_equal(p) << std::endl;

    Posit p4(6, 1);
    std::cout << p4.is_zero() << ' ' << p4.ns() << ' ' << p4.es() << ' ' << p4.npat()
        << ' ' << p4.useed() << ' ' << p4.minpos().to_string() << ' ' << p4.maxpos() << ' '
        << p4.qsize() << ' ' << p4.qextra() << std::endl;
}