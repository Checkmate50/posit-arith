#include "frac.hpp"
#include <math.h>

// https://stackoverflow.com/questions/26643695/converting-a-floating-point-decimal-value-to-a-fraction
uint64_t gcd(uint64_t a, uint64_t b)
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

void Frac::init(bool sign, uint64_t numerator, uint64_t denominator) {
    // assumes the numerator and denominator have already been reduced
    this->sign = sign;
    this->numerator = numerator;
    this->denominator = denominator;
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

    uint64_t gcd_ = gcd(round(fraction * precision), precision);

    uint64_t denom = static_cast<uint64_t>(precision / gcd_);

    auto wholen = static_cast<uint64_t>(std::abs(whole)) * denom;
    uint64_t num = wholen + static_cast<uint64_t>(round(fraction * precision) / gcd_);
    init(value < 0, num, denom);
}

Frac::Frac(bool sign, uint64_t numerator, uint64_t denominator) {
    uint64_t gcd_ = gcd(numerator, denominator);
    init(sign, numerator / gcd_, denominator / gcd_);
}

std::string Frac::to_string() const {
    std::string signs = "";
    if (sign)
        signs = "-";
    return signs + std::to_string(numerator) + " / " + std::to_string(denominator);
}

double Frac::to_double() const {
    double neg = 1;
    if (sign)
        neg = -1;
    return neg * static_cast<double>(numerator) / static_cast<double>(denominator);
}

Frac Frac::neg() const {
    Frac f(!sign, numerator, denominator);
    return f;
}

Frac Frac::add(const Frac& other) const {
    uint64_t common_denom = denominator * other.denominator;
    uint64_t mynum = numerator * other.denominator;
    uint64_t othernum = other.numerator * denominator;
    uint64_t num_result;
    bool nsign;
    if (sign == other.sign) {
        nsign = sign;
        num_result = mynum + othernum;
    }
    else if(mynum > othernum) {
        nsign = sign;
        num_result = mynum - othernum;
    }
    else {
        nsign = other.sign;
        num_result = othernum - mynum;
    }
    return Frac(nsign, num_result, common_denom);
}

Frac Frac::sub(const Frac& other) const {
    return add(other.neg());
}

Frac Frac::mul(const Frac& other) const {
    return Frac(sign ^ other.sign, numerator * other.numerator, 
        denominator * other.denominator);
}

Frac Frac::div(const Frac& other) const {
    return mul(Frac(other.sign, other.denominator, other.numerator));
}

Frac Frac::pow2(int amount) const {
    return Frac(sign, numerator << amount, denominator);
}

Frac Frac::operator-() const {
    return neg();
}

Frac Frac::operator+(const Frac& other) const {
    return add(other);
}

Frac Frac::operator-(const Frac& other) const {
    return sub(other);
}

Frac Frac::operator*(const Frac& other) const {
    return mul(other);
}

Frac Frac::operator/(const Frac& other) const {
    return div(other);
}