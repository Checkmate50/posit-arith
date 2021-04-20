#include <math.h>
#include <assert.h>
#include "posit.hpp"

void Posit::init(uint64_t bits, uint8_t nbits, uint8_t es) {
    assert(nbits >= es);
    assert(nbits <= 64);
    assert(nbits > 1); // just don't allow posits of size 1
    this->bits = bits;
    this->nbits = nbits;
    this->esm = es;
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

uint8_t Posit::ss() const {
    return 1;
}

uint8_t Posit::rs() const {
    uint64_t bitcheck = static_cast<uint64_t>(1) << (nbits - 2);
    bool rsign = bits ^ bitcheck;
    uint8_t count = 1;
    while (bitcheck > 0 && (static_cast<bool>(bits ^ bitcheck) == rsign)) {
        bitcheck >>= 1;
        count++;
    }
    return count;
}

uint8_t Posit::es() const {
    return std::min(std::max(nbits - ss() - rs(), static_cast<uint8_t>(0)), esm);
}

uint8_t Posit::fs() const{
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
    return static_cast<uint64_t>(1) << static_cast<uint64_t>(log2(nbits - 2 * pow(2, esm + 2) + 5));
}

uint64_t Posit::qextra() const {
    return qsize() - (nbits - 2)*static_cast<uint64_t>(pow(2, esm + 2));
}