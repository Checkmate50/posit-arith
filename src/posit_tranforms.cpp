#include <math.h>
#include <assert.h>
#include "posit.hpp"
#include <iostream>
#include <limits>
#include <math.h>

Frac Posit::to_frac() const {
    // Basically p2x of https://posithub.org/docs/Posits4.pdf
    if (is_zero())
        return Frac(false, 0, 1);
    if (is_inf())
        return Frac(false, 1, 0);
    auto s = is_neg();
    uint64_t num = 1;
    uint64_t denom = 1;

    auto const us = useed();
    int k = regime_val();
    if (k >= 0)
        num *= pow(us, k);
    else
        denom *= pow(us, -k);

    num *= 1 << esbits_s();

    auto const frb = frbits();
    num *= frb + (static_cast<uint64_t>(1) << fs()); // fraction + 1, where 1 is 2**fs() / 2**fs()
    denom *= static_cast<uint64_t>(1) << fs();

    return Frac(s, num, denom);
}

double Posit::to_double() const{ 
    // basically just calls the Frac.to_double() function
    if (is_inf()) {
        return std::numeric_limits<double>::infinity();
    }
    return to_frac().to_double();
}

std::string Posit::to_string() const {
    std::string result = "";
    auto b = static_cast<uint64_t>(1) << (nbits - 1);
    for (int i = 0; i < nbits; i++) {
        result += bits & b ? "1" : "0";
        b >>= 1;
    }
    return result;
}