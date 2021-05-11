#include <math.h>
#include <assert.h>
#include "posit.hpp"
#include <iostream>
#include <limits>
#include <math.h>

void Posit::init(uint64_t bits, uint8_t nbits, uint8_t es) {
    assert(nbits >= es);
    assert(nbits <= 64);
    assert(nbits > 1); // just don't allow posits of size 1
    this->bits = bits;
    this->nbits = nbits;
    this->esm = es;
}

uint64_t Posit::signed_bits() const {
    auto negcheck = (static_cast<uint64_t>(1) << (nbits - 1));
    bool isneg = bits & negcheck;
    if (!isneg)
        return bits;
    auto result = ~bits + 1;
    result |= negcheck; // reset the neg bit
    return result;
}

Posit::Posit() {
    init(0, 32, 8);
}

Posit::Posit(uint8_t nbits, uint8_t es) {
    init(0, nbits, es);
}

Posit::Posit(uint64_t bits) {
    init(bits, 32, 8);
}

Posit::Posit(uint64_t bits, uint8_t nbits, uint8_t es) {
    init(bits, nbits, es);
}

bool Posit::is_equal(const Posit& other) const {
    return nbits == other.nbits && esm == other.esm && bits == other.bits; // placeholder until we allow conversions
}

bool Posit::is_zero() const {
    return is_equal(Posit(nbits, esm));
}

bool Posit::is_inf() const {
    return is_equal(Posit(static_cast<uint64_t>(1) << (nbits - 1), nbits, esm));
}

bool Posit::is_neg() const {
    return bits & (static_cast<uint64_t>(1) << (nbits - 1));
}

int Posit::ns() const {
    return nbits;
}

int Posit::ss() const {
    return 1;
}

int Posit::rs() const {
    uint64_t bitcheck = static_cast<uint64_t>(1) << (nbits - 2);
    auto sbits = signed_bits();
    bool rsign = sbits & bitcheck;
    uint8_t count = 1;
    while (bitcheck > 1 && (static_cast<bool>(sbits & bitcheck) == rsign)) {
        bitcheck >>= 1;
        count++;
    }
    return count;
}

int Posit::es() const {
    return std::min(std::max(nbits - ss() - rs(), 0), static_cast<int>(esm));
}

int Posit::fs() const{
    return std::max(nbits - ss() - rs() - es(), 0);
}

uint64_t Posit::npat() const {
    return static_cast<uint64_t>(1) << nbits;
}

uint64_t Posit::useed() const {
    return static_cast<uint64_t>(1) << (static_cast<uint64_t>(1) << esm);
}

uint64_t Posit::maxpos() const {
    return static_cast<uint64_t>(pow(useed(), nbits-2));
}

Frac Posit::minpos() const {
    return Frac(false, 1, static_cast<uint64_t>(pow(useed(), nbits-2)));
}

uint64_t Posit::qsize() const {
    return static_cast<uint64_t>(1) << static_cast<int>(std::ceil(log2((nbits - 2) * pow(2, esm + 2) + 5)));
}

uint64_t Posit::qextra() const {
    return qsize() - (nbits - 2)*static_cast<uint64_t>(pow(2, esm + 2));
}

bool Posit::signbit() const {
    return is_neg();
} 

uint64_t mask_bits(uint64_t bits, int size, int offset) {
    uint64_t mask = 0;
    for (int i = 0; i < size; i++)
        mask = (mask << 1) + 1;
    mask <<= offset;
    return bits & mask;
}

uint64_t Posit::regime() const {
    return mask_bits(signed_bits(), rs(), es() + fs());
}

uint64_t Posit::esbits() const {
    return mask_bits(signed_bits(), es(), fs());
}

uint64_t Posit::frbits() const {
    return mask_bits(signed_bits(), fs(), 0);
}

int Posit::regime_val() const {
    auto bitcheck = static_cast<uint64_t>(1) << (nbits - 2);
    auto const rsr = rs();
    if (is_zero() || is_inf())
        return 0 - rsr; // all zero case
    auto sb = signed_bits();
    if (sb & bitcheck) {
        if ((rsr == (nbits - 1)) && (sb & 1))
            return rsr - 1; // special case for all ones
        return rsr - 2;
    }
    return 1 - rsr;
}

uint64_t Posit::esbits_s() const {
    return (esbits() >> fs()) << (esm - es());
}