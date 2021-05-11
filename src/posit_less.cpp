#include "posit.hpp"

bool Posit::is_less(const Posit& other) const {
    if (nbits != other.nbits) // placeholder for conversions
        return false;
    if (esm != other.esm)
        return false;
    bool isi = is_inf();
    bool oti = other.is_inf();
    if (isi && !oti) // let's just put infinity at the top
        return false;
    if (!isi && oti)
        return true;

    bool isn = is_neg();
    bool otn = other.is_neg();
    // obviously negative < positive, and vice-versa
    if (isn && !otn)
        return true;
    if (!isn && otn)
        return false;
    // This is very surprising that this _just works_
    // to see why, observe that bits < other.bits only when regime < other.regime
    //   || regime == other.regime && exp < other.exp || ... && fraction < other.fraction
    // Then, observe that those conditions are equivalent to actual comparison result
    // Specifically, observe that useed grows faster than 2^(max_es-min_es)
    //  and that the fraction grows less than 2 trivially (by definition)
    // It also works for negatives!  Cause of posit inversion
    return bits < other.bits;
}