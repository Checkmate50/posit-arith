#include <math.h>
#include <assert.h>
#include "posit.hpp"
#include <iostream>
#include <limits>
#include <math.h>

bool Posit::operator==(const Posit& other) const {
    return is_equal(other);
}

bool Posit::operator<=(const Posit& other) const {
    return is_equal(other) || is_less(other);
}

bool Posit::operator>=(const Posit& other) const {
    return is_equal(other) || other.is_less(*this);
}

bool Posit::operator<(const Posit& other) const {
    return is_less(other);
}

bool Posit::operator>(const Posit& other) const {
    return other.is_less(*this);
}

Posit Posit::operator-() const {
    return negate();
}

Posit Posit::operator+(const Posit& other) const {
    return add(other);
}

// Posit Posit::operator-(const Posit& other) const {
//     return sub(other);
// }

// Posit Posit::operator*(const Posit& other) const {
//     return mul(other);
// }

// Posit Posit::operator/(const Posit& other) const {
//     return div(other);
// }