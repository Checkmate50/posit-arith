#pragma once

#include <stdint.h>
#include <string>
#include <memory>

class Frac;
using frac_ptr = std::unique_ptr<Frac>;

class Frac {
private:
    bool sign;
    uint64_t numerator;
    uint64_t denominator;
    void init(bool sign, uint64_t numerator, uint64_t denominator) {
        this->sign = sign;
        this->numerator = numerator;
        this->denominator = denominator;
    }
public:
    Frac(int value);
    Frac(double value); // a lazy conversion, can easily overflow
    Frac(bool sign, uint64_t numerator, uint64_t denominator);

    std::string as_string() const;
    double      as_double() const;

    frac_ptr neg() const;
    frac_ptr add(frac_ptr other) const; // minimal addition implementation
    frac_ptr sub(frac_ptr other) const;
    frac_ptr mul(frac_ptr other) const;
    frac_ptr div(frac_ptr other) const;
    frac_ptr pow2(int val) const;
};