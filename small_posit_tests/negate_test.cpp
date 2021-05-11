#include "../src/posit.hpp"
#include <iostream>

int main() {
    auto const size = 8;
    auto const es = 3;
    for (uint64_t i = 0; i < (static_cast<uint64_t>(1) << size); i++) {
        auto l = -Posit(i, size, es).to_double();
        auto r = -(Posit(i, size, es).to_double());
        std::cout << (l == r);
        if (l != r)
            std::cout << std::endl << l << ' ' << r << std::endl;
    }
    std::cout << std::endl;
}