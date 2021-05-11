#include "frac.hpp"
#include <math.h>
#include <numeric>

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

    uint64_t gcd_ = std::gcd(static_cast<uint64_t>(round(fraction * precision)), precision);

    uint64_t denom = static_cast<uint64_t>(precision / gcd_);

    auto wholen = static_cast<uint64_t>(std::abs(whole)) * denom;
    uint64_t num = wholen + static_cast<uint64_t>(round(fraction * precision) / gcd_);
    init(value < 0, num, denom);
}

Frac::Frac(bool sign, uint64_t numerator, uint64_t denominator) {
    uint64_t gcd_ = std::gcd(numerator, denominator);
    init(sign, numerator / gcd_, denominator / gcd_);
}

bool Frac::is_equal(const Frac& other) const {
    if (sign != other.sign)
        return false;
    uint64_t lc = std::lcm(denominator, other.denominator);
    auto left = numerator * (lc / denominator);
    auto right = other.numerator * (lc / other.denominator);
    return left == right;
}

bool Frac::is_less(const Frac& other) const {
    if (sign && !(other.sign))
        return false;
    if (!sign && other.sign)
        return true;
    uint64_t lc = std::lcm(denominator, other.denominator);
    auto left = numerator * (lc / denominator);
    auto right = other.numerator * (lc / other.denominator);
    if (sign)
        return right < left;
    else
        return left < right;
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

bool Frac::operator==(const Frac& other) const {
    return is_equal(other);
}

bool Frac::operator<=(const Frac& other) const {
    return is_equal(other) || is_less(other);
}

bool Frac::operator>=(const Frac& other) const {
    return is_equal(other) || other.is_less(*this);
}

bool Frac::operator<(const Frac& other) const {
    return is_less(other);
}

bool Frac::operator>(const Frac& other) const {
    return other.is_less(*this);
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