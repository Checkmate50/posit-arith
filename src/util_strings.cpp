#include "util.hpp"
#include <string>

std::string get_python_header() {
    std::string result;
    result += "from bitstring import Bits\n";
    return result;
}

std::string python_bit_repr(float f) {
    std::string result;
    result += "Bits(\"0b";
    result += get_float_bits(f);
    result += "\").float";
    return result;
}

std::string python_bit_repr(double d) {
    std::string result;
    result += "Bits(\"0b";
    result += get_double_bits(d);
    result += "\").float";
    return result;
}

std::string float_op(std::string op, float f, float res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(f);
    result += ',';
    result += python_bit_repr(res);
    result += "]\n";
    return result;
}

std::string float_op(std::string op, float f1, float f2, float res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(f1);
    result += ',';
    result += python_bit_repr(f2);
    result += ',';
    result += python_bit_repr(res);
    result += "]\n";
    return result;
}

std::string float_comp(std::string op, float f, bool res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(f);
    result += ',';
    result += res ? "True" : "False";
    result += "]\n";
    return result;
}

std::string float_comp(std::string op, float f1, float f2, bool res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(f1);
    result += ',';
    result += python_bit_repr(f2);
    result += ',';
    result += res ? "True" : "False";
    result += "]\n";
    return result;
}

std::string double_op(std::string op, double d, double res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(d);
    result += ',';
    result += python_bit_repr(res);
    result += "]\n";
    return result;
}

std::string double_op(std::string op, double d1, double d2, double res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(d1);
    result += ',';
    result += python_bit_repr(d2);
    result += ',';
    result += python_bit_repr(res);
    result += "]\n";
    return result;
}

std::string double_comp(std::string op, double d, bool res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(d);
    result += ',';
    result += res ? "True" : "False";
    result += "]\n";
    return result;
}

std::string double_comp(std::string op, double d1, double d2, bool res) {
    std::string result = "x = [";
    result += op;
    result += ',';
    result += python_bit_repr(d1);
    result += ',';
    result += python_bit_repr(d2);
    result += ',';
    result += res ? "True" : "False";
    result += "]\n";
    return result;
}