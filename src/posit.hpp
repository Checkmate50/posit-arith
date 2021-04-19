#pragma once

#include <stdint.h>
#include <string>

// https://github.com/libcg/bfp for some reference
// https://posithub.org/docs/Posits4.pdf for general reference
class Posit {
private:
    // Support posits of up to size 64
    uint64_t backing_bits;
    int es_max;
public:
    Posit();
    Posit(uint32_t bits);
    Posit(int es);
    Posit(uint32_t bits, int es);

    bool isEqual(Posit other) const;
    bool isZero() const;
    bool isInf() const;
    bool isNeg() const;

    uint64_t npat()     const; // number of possible representations
    uint64_t useed()    const; // 2^2^es
    uint64_t maxval()   const; // the maximum value (the minimum is 1/maxval)
    uint64_t qsize()    const; // the quire size
    uint64_t qextra()   const; // extra bits for overflow

    int ss() const; // sign size
    int rs() const; // regime size
    int es() const; // exponent size
    int fs() const; // fractional size

    int         signbit()   const; // get the sign bit
    uint64_t    regime()    const; // get the regime bits
    uint64_t    esbits()    const; // get the exponent bits
    uint64_t    frbits()    const; // get the fractional bits

    double      as_double()    const; // Represent this posit as an approximate double
    std::string as_frac()      const; // Represent this posit as a fraction in a string
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