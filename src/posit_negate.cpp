#include "posit.hpp"

Posit Posit::negate() const {
    // A cool application of posit representation theory that this _just works_
    return Posit(~bits + 1, nbits, esm);
}