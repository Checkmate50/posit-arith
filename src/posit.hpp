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
public:
    Posit();
    Posit(uint8_t nbits, uint8_t es);
    Posit(uint64_t bits);
    Posit(uint64_t bits, uint8_t nbits, uint8_t es);

    bool is_equal(const Posit& other) const;
    bool is_zero() const;
    bool is_inf() const;
    bool is_neg() const;

    uint8_t ns() const; // number of bits
    uint8_t ss() const; // sign size
    uint8_t rs() const; // regime size
    uint8_t es() const; // exponent size
    uint8_t fs() const; // fractional size

    uint64_t npat()     const; // number of possible representations
    uint64_t useed()    const; // 2^2^es
    Frac     minpos()   const; // the minimum value (1 / maxval)
    uint64_t maxpos()   const; // the maximum value
    uint64_t qsize()    const; // the quire size
    uint64_t qextra()   const; // extra bits for overflow

    int         signbit()   const; // get the sign bit
    uint64_t    regime()    const; // get the regime bits
    uint64_t    esbits()    const; // get the exponent bits
    uint64_t    frbits()    const; // get the fractional bits

    double      as_double()    const; // Represent this posit as an approximate double
    Frac        as_frac()      const; // Represent this posit as a fraction
    std::string as_string()    const; // Represent the bits of this posit in a string
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