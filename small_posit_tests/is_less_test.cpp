#include "../src/posit.hpp"
#include <iostream>

int main() {
    auto const size = 8;
    auto const es = 2;
    for (uint64_t i = 0; i < (static_cast<uint64_t>(1) << size); i++) {
        for (uint64_t j = 0; j < (static_cast<uint64_t>(1) << size); j++) {
            Posit l(i, size, es);
            Posit r(j, size, es);
            if ((l < r) && l.to_double() >= r.to_double())
                std::cout << "first:\t" << l.to_string() << ' ' << r.to_string() << ' '
                    << l.to_double() << ' ' << r.to_double() << std::endl;
            if ((l >= r) && l.to_double() < r.to_double())
                std::cout << "second:\t" << l.to_string() << ' ' << r.to_string() << ' '
                    << l.to_double() << ' ' << r.to_double() << std::endl;
        }
    }
    std::cout << std::endl;
}