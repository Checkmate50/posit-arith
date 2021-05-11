#include "posit.hpp"
#include <iostream>
#include <algorithm>

uint64_t push_regime(int regime_diff, uint64_t frbits, uint8_t esm) {
    return frbits >> ((esm + 1) * regime_diff);
}

Posit Posit::add(const Posit& other) const {
    if (nbits != other.nbits) // placeholder for conversions
        return Posit(nbits, esm);
    if (esm != other.esm)
        return Posit(nbits, esm);

    // infinity special case
    if (is_inf())
        return Posit(bits, nbits, esm);
    if (other.is_inf())
        return Posit(other.bits, nbits, esm);

    // First, put the components in different things
    int rl = regime_val();
    int rr = other.regime_val();

    uint64_t el = esbits_s();
    uint64_t er = other.esbits_s();

    int fsl = fs();
    int fsr = other.fs();

    // Add the hidden bit to the fraction as part of this
    uint64_t fl = frbits() + (static_cast<uint64_t>(1) << fsl);
    uint64_t fr = other.frbits() + (static_cast<uint64_t>(1) << fsr);

    //std::cout << rl << " " << rr << std::endl;

    // second, unify the regime
    if (rl < rr) {
        // el is put at the front of the fraction
        fl = push_regime(rr - rl, fl + (el << (fsl + 1)), esm); 
        el = 0; // exponent always gets wiped
        rl = rr; // regimes are now unified
    } else if (rr < rl) {
        fr = push_regime(rl - rr, fr + (er << (fsr + 1)), esm);
        er = 0;
        rr = rl;
    }

    // third, unify the exponent
    if (el < er) {
        fl >>= er - el;
        el = er;
    } else if (er < el) {
        fr >>= el - er;
        er = el;
    }

    // Fourth, calculate the fraction
    uint64_t fr_res = 0;
    bool s = 0;
    // if equal signs, do addition
    if (is_neg() == other.is_neg()) {
        s = signbit();
        fr_res = fl + fr;
    }
    // otherwise do subtraction
    else {
        // special case to make sure we don't make infinity
        if (fl == fr) {
            return Posit(nbits, esm);
        } else if (fl > fr) {
            s = signbit();
            fr_res = fl - fr;
        } else { // fr > fl
            s = other.signbit();
            fr_res = fr - fl;
        }
    }

    // Fifth, calculate the final exponent and regime
    long long es_res = static_cast<long long>(el);
    int r_res = rl;

    int s_s = 1;
    int r_res_s = r_res >= 0 ? r_res + 2 : 1 - r_res;
    // calculate the sizes (can be reused from earlier, explicit here for reasons)
    int es_res_s = std::min(std::max(nbits - s_s - r_res_s, 0), static_cast<int>(esm));
    int fr_res_s = std::max(nbits - s_s - r_res_s - es_res_s, 0);

    // std::cout << r_res_s << " " << es_res_s << " " << fr_res_s << std::endl;
    // std::cout << s << " " << r_res << " " << es_res << " " << fr_res << std::endl;

    // This includes handling overflow
    // I _think_ the following two blocks can actually be cut, but I can't work out the math
    if (fr_res & (static_cast<uint64_t>(1) << (fr_res_s + 1))) {// if frac overflow
        es_res += static_cast<long long>(1) << (esm - es_res_s); // a surprising result, but works...
        fr_res >>= 1;
    }
    if (es_res & (static_cast<uint64_t>(1) << esm)) { // if exp overflow
        r_res += 1;
        es_res >>= 1; // to account for the regime adding one
        fr_res = push_regime(1, fr_res + (es_res << (fr_res_s + 1)), esm);
        es_res = 0;
        if (r_res >= nbits - 1)
            return Posit(static_cast<uint64_t>(1) << (nbits - 1), nbits, esm); // infinity
        // recalculate the sizes since they might have changed
        r_res_s = r_res >= 0 ? r_res + 2 : 1 - r_res;
        es_res_s = std::min(std::max(nbits - s_s - r_res_s, 0), static_cast<int>(esm));
        fr_res_s = std::max(nbits - s_s - r_res_s - es_res_s, 0);
        fr_res += static_cast<uint64_t>(1) << fr_res_s; // re-add hidden bit, which got pushed off cause reasons
    }

    // this loop can be directly calculated to avoid the loop, but I'm lazy and the math is tricky
    while (!(fr_res & (static_cast<uint64_t>(1) << fr_res_s))) { // fr_res should never be 0 for reasons
        es_res -= static_cast<long long>(1) << (esm - es_res_s); // a surprising result, but works...
        fr_res <<= 1;
    }

    if (es_res < 0) { // if exp became negative
        r_res -= 1;
        es_res += static_cast<long long>(1) << esm; // to account for the regime adding one
        if (r_res < 1 - nbits)
            return Posit(nbits, esm); // zero
        // recalculate the sizes since they might have changed
        r_res_s = r_res >= 0 ? r_res + 2 : 1 - r_res;
        es_res_s = std::min(std::max(nbits - s_s - r_res_s, 0), static_cast<int>(esm));
        fr_res_s = std::max(nbits - s_s - r_res_s - es_res_s, 0);
    }

    // std::cout << r_res_s << " " << es_res_s << " " << fr_res_s << std::endl;
    // std::cout << s << " " << r_res << " " << es_res << " " << fr_res << std::endl;

    // Finally, construct the resulting posit
    uint64_t result = static_cast<uint64_t>(s) << (nbits - 1);
    if (r_res < 0)
        result += static_cast<uint64_t>(1) << (fr_res_s + es_res_s);
    else {
        if (r_res == nbits - 2)
            result += ~static_cast<uint64_t>(0) >> (64 - nbits + s_s);
        // note the exra +1 to account for the 0 at the end
        else
            result += ~static_cast<uint64_t>(0) >> (64 - nbits + s_s + fr_res_s + es_res_s + 1)
                << (fr_res_s + es_res_s + 1);
    }
    if (fr_res_s > 0)
        result += es_res << fr_res_s;
    else
        result += es_res >> (esm - es_res_s);
    result += fr_res - (static_cast<uint64_t>(1) << fr_res_s); // remove hidden bit

    if (s) { // negate the bits
        result = (~result + 1) << (64 - nbits) >> (64 - nbits); // shift to clean bits
        result |= static_cast<uint64_t>(1) << (nbits - 1);
    }

    // std::cout << result << std::endl;

    return Posit(result, nbits, esm);
}