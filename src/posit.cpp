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
    return bits == other.bits && nbits == other.nbits && esm == other.esm;
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
    if (signed_bits() & bitcheck) {
        if (rs() == nbits - 1 && signed_bits() & 1)
            return rs() - 1; // special case for all ones
        return rs() - 2;
    }
    return -rs() + 1;
}

uint64_t Posit::esbits_s() const {
    return (esbits() >> fs()) << (esm - es());
}

Frac Posit::to_frac() const {
    // Basically p2x of https://posithub.org/docs/Posits4.pdf
    if (is_zero())
        return Frac(false, 0, 1);
    if (is_inf())
        return Frac(false, 1, 0);
    auto s = is_neg();
    uint64_t num = 1;
    uint64_t denom = 1;

    
    int k = regime_val();
    if (k >= 0)
        num *= pow(useed(), k);
    else
        denom *= pow(useed(), -k);

    num *= 1 << esbits_s();
    num *= (frbits() << 1) + 1;
    if (frbits() > 0)
        denom *= 1 << fs();

    return Frac(s, num, denom);
}

double Posit::to_double() const{ 
    // basically just calls the Frac.to_double() function
    if (is_inf())
        return std::numeric_limits<double>::infinity();
    return to_frac().to_double();
}

std::string Posit::to_string() const {
    std::string result = "";
    auto b = static_cast<uint64_t>(1) << (nbits - 1);
    for (int i = 0; i < nbits; i++) {
        result += bits & b ? "1" : "0";
        b >>= 1;
    }
    return result;
}