#pragma once

#include "frac.hpp"
#include <stdint.h>
#include <string>
#include <memory>

class Posit;
using posit_ptr = std::unique_ptr<Posit>;

// https://github.com/libcg/bfp for some reference
// https://posithub.org/docs/Posits4.pdf for general reference
class Posit {
private:
    // Support posits of up to size 64
    uint64_t bits;
    uint8_t nbits;
    uint8_t esm;
    void init(uint64_t bits, uint8_t nbits, uint8_t es);
    uint64_t signed_bits() const;
public:
    Posit();
    Posit(uint8_t nbits, uint8_t es);
    Posit(uint64_t bits);
    Posit(uint64_t bits, uint8_t nbits, uint8_t es);

    bool        is_equal(const Posit& other) const;
    bool        is_zero() const;
    bool        is_inf() const;
    bool        is_neg() const;

    int         ns() const; // number of bits
    int         ss() const; // sign size
    int         rs() const; // regime size
    int         es() const; // exponent size
    int         fs() const; // fractional size

    uint64_t    npat()     const; // number of possible representations
    uint64_t    useed()    const; // 2^2^es
    Frac        minpos()   const; // the minimum value (1 / maxval)
    uint64_t    maxpos()   const; // the maximum value
    uint64_t    qsize()    const; // the quire size
    uint64_t    qextra()   const; // extra bits for overflow

    bool        signbit()   const; // get the sign bit
    uint64_t    regime()    const; // get the regime bits
    uint64_t    esbits()    const; // get the exponent bits
    uint64_t    frbits()    const; // get the fractional bits
    int         regime_val()const; // get the regime value (the number of bits in the sequence)
    uint64_t    esbits_s()  const; // get the exponent bits shifted to the right

    Frac        to_frac()      const; // Represent this posit as a fraction
    double      to_double()    const; // Represent this posit as an approximate double (i.e. just the fraction as a double)
    std::string to_string()    const; // Represent the bits of this posit in a string

    bool        is_less(const Posit& other) const; // Return whether this is less than the other posit
    Posit       negate()                    const; // Adds this Posit to other
    Posit       add(const Posit& other)     const; // Adds this Posit to other
    Posit       sub(const Posit& other)     const; // Subtracts other from this Posit
    Posit       mul(const Posit& other)     const; // Multiplies this posit by the other
    Posit       div(const Posit& other)     const; // Divide other from this posit

    bool        operator==(const Posit& other)  const;
    bool        operator<=(const Posit& other)  const;
    bool        operator>=(const Posit& other)  const;
    bool        operator<(const Posit& other)   const;
    bool        operator>(const Posit& other)   const;

    Posit       operator-()                     const;
    Posit       operator+(const Posit& other)   const;
    Posit       operator-(const Posit& other)   const;
    Posit       operator*(const Posit& other)   const;
    Posit       operator/(const Posit& other)   const;
};

class Posit32 : public Posit
{
public:
    Posit32();
    Posit32(Posit v);
    Posit32(float v);
    Posit32(double v);
    Posit32(Posit v, int es);
    Posit32(float v, int es);
    Posit32(double v, int es);
};