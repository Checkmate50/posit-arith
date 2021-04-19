#pragma once

#include <stdint.h>
#include <string>

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

    Frac neg(Frac other) const;
    Frac add(Frac other) const; // minimal addition implementation
    Frac sub(Frac other) const;
    Frac mul(Frac other) const;
    Frac div(Frac other) const;
    Frac pow2(int val) const;
};