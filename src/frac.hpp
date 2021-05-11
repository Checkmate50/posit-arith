#pragma once

#include <stdint.h>
#include <string>
#include <memory>

class Frac;
using frac_ptr = std::unique_ptr<Frac>;

// Guarantees the invariant that fractions are irreducible
class Frac {
private:
    bool sign;
    uint64_t numerator;
    uint64_t denominator;
    void init(bool sign, uint64_t numerator, uint64_t denominator);
public:
    Frac(int value);
    Frac(double value); // a lazy conversion, can easily overflow
    Frac(bool sign, uint64_t numerator, uint64_t denominator);

    std::string to_string() const;
    double      to_double() const;

    bool is_equal(const Frac& other)    const;
    bool is_less(const Frac& other)     const; // uses multiplication, so can overflow

    Frac neg() const;
    Frac add(const Frac& other) const; // enforces gcd-based minimization, but might overflow
    Frac sub(const Frac& other) const;
    Frac mul(const Frac& other) const;
    Frac div(const Frac& other) const;
    Frac pow2(int amount) const; // Frac^(2^amount)

    bool operator==(const Frac& other)  const;
    bool operator<=(const Frac& other)  const;
    bool operator>=(const Frac& other)  const;
    bool operator<(const Frac& other)   const;
    bool operator>(const Frac& other)   const;

    Frac operator-() const;
    Frac operator+(const Frac& other) const;
    Frac operator-(const Frac& other) const;
    Frac operator*(const Frac& other) const;
    Frac operator/(const Frac& other) const;
};