#include "../src/posit.hpp"
#include <iostream>

int main() {
    auto const size = 32;
    auto const es = 2;
    auto const eps = 0.1;
    for (uint64_t i = 0; i < (static_cast<uint64_t>(1) << size); i++) {
        for (uint64_t j = 0; j < (static_cast<uint64_t>(1) << size); j++) {
            Posit l(i, size, es);
            Posit r(j, size, es);
            Posit res = l + r;
            double dres = l.to_double() + r.to_double();
            if (res.is_inf()) {
                std::cout << l.to_string() << ' ' << r.to_string() << std::endl;
                continue;
            }
            // we take dres to have infinite precision relative to res
            if (res.to_double() / dres > 1+eps)
                std::cout << "first:\t" << l.to_string() << ' ' << r.to_string() << ' '
                    << l.to_double() << ' ' << r.to_double() << ' ' 
                    << res.to_double() << ' '  << dres << std::endl;
            if (res.to_double() / dres < 1-eps)
                std::cout << "second:\t" << l.to_string() << ' ' << r.to_string() << ' '
                    << l.to_double() << ' ' << r.to_double() << ' ' 
                    << res.to_double() << ' '  << dres << std::endl;
        }
    }
    std::cout << std::endl;
}