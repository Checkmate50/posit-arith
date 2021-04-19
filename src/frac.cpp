#pragma once

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
    uint64_t result;
    if (value < 0)
        result = static_cast<uint64_t>(-value);
    else
        result = static_cast<uint64_t>(value);
    Frac(value < 0, result, 1);
}

Frac::Frac(double value) {
    double whole;
    double fraction = modf(value, &whole);
    // copied from https://stackoverflow.com/questions/26643695/converting-a-floating-point-decimal-value-to-a-fraction
    const long precision = 1000000000; // This is the accuracy.

    long gcd_ = gcd(round(fraction * precision), precision);

    uint64_t denom = static_cast<uint64_t>(precision / gcd_);

    uint64_t wholen;
    if (value < 0)
        wholen = static_cast<uint64_t>(-whole);
    else
        wholen = static_cast<uint64_t>(whole);
    wholen *= denom;
    uint64_t num = wholen + static_cast<uint64_t>(round(fraction * precision) / gcd_);
    Frac(value < 0, num, denom);
}

Frac::Frac(bool sign, uint64_t numerator, uint64_t denominator) {
    this->sign = sign;
    this->numerator = numerator;
    this->denominator = denominator;
}

double Frac::as_double() const {
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

std::string Frac::as_string() const {
    std::string signs = "";
    if (sign)
        signs = "-";
    return signs + std::to_string(numerator) + " / " + std::to_string(denominator);
}