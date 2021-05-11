#include "util.hpp"
#include <string>
#include <cstring> // for memcpy
#include <stdint.h>
#include <limits>
#include <iostream>

std::string get_float_bits(float f) {
    uint32_t bits;
    memcpy(&bits, &f, sizeof(f));
    std::string result = "";
    for (uint64_t i = (static_cast<uint32_t>(1) << 31); i > 0; i >>= 1)
        result += i & bits ? "1" : "0";
    return result;
}

std::string get_double_bits(double d) {
    uint64_t bits;
    memcpy(&bits, &d, sizeof(d));
    std::string result = "";
    for (uint64_t i = (static_cast<uint64_t>(1) << 63); i > 0; i >>= 1)
        result += i & bits ? "1" : "0";
    return result;
}

float int_to_float(uint32_t i) {
    float result;
    memcpy(&result, &i, sizeof(result));
    return result;
}

double ll_to_double(uint64_t l) {
    double result;
    memcpy(&result, &l, sizeof(result));
    return result;
}

float get_float_inf() {
    static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<float>::infinity();
}   

float get_float_neginf() {
    static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
    return -std::numeric_limits<float>::infinity();
}

float get_float_nan() {
    static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<float>::quiet_NaN();
}

float get_float_max() {
    static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<float>::max();
}

float get_float_min() {
    static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<float>::min();
}

double get_double_inf() {
    static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<double>::infinity();
}   

double get_double_neginf() {
    static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");
    return -std::numeric_limits<double>::infinity();
}

double get_double_nan() {
    static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<double>::quiet_NaN();
}

double get_double_max() {
    static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<double>::max();
}

double get_double_min() {
    static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");
    return std::numeric_limits<double>::min();
}