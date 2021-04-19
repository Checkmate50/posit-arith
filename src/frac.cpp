#include "frac.hpp"
#include <math.h>

// https://stackoverflow.com/questions/26643695/converting-a-floating-point-decimal-value-to-a-fraction
long gcd(long a, long b)
{
    if (a == 0)
        return b;
    else if (b == 0)
        return a;

    if (a < b)
        return gcd(a, b % a);
    else
        return gcd(b, a % b);
}

Frac::Frac(int value) {
    auto result = static_cast<uint64_t>(std::abs(value));
    init(value < 0, result, 1);
}

Frac::Frac(double value) {
    double whole;
    double fraction = modf(value, &whole);
    // copied from https://stackoverflow.com/questions/26643695/converting-a-floating-point-decimal-value-to-a-fraction
    const long precision = 1000000000; // This is the accuracy.

    long gcd_ = gcd(round(fraction * precision), precision);

    uint64_t denom = static_cast<uint64_t>(precision / gcd_);

    auto wholen = static_cast<uint64_t>(std::abs(whole)) * denom;
    uint64_t num = wholen + static_cast<uint64_t>(round(fraction * precision) / gcd_);
    init(value < 0, num, denom);
}

Frac::Frac(bool sign, uint64_t numerator, uint64_t denominator) {
    init(sign, numerator, denominator);
}

std::string Frac::as_string() const {
    std::string signs = "";
    if (sign)
        signs = "-";
    return signs + std::to_string(numerator) + " / " + std::to_string(denominator);
}

double Frac::as_double() const {
    double neg = 1;
    if (sign)
        neg = -1;
    return neg * static_cast<double>(numerator) / static_cast<double>(denominator);
}

frac_ptr Frac::neg() const {
    auto f = std::make_unique<Frac>(!sign, numerator, denominator);
    return f;
}