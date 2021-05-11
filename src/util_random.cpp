#include "util.hpp"
#include <stdint.h>

std::mt19937_64 setup_random() {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    return eng;
}

double get_full_float_random(std::uniform_int_distribution<unsigned int>& distr, std::mt19937_64& eng) {
    return int_to_float(static_cast<uint32_t>(distr(eng)));
}

double get_smol_float_random(std::uniform_int_distribution<unsigned int>& distr, 
        std::mt19937_64& eng) {
    uint32_t num = static_cast<uint32_t>(distr(eng));
    uint32_t num1 = static_cast<uint32_t>(distr(eng));
    uint32_t num2 = static_cast<uint32_t>(distr(eng));
    uint32_t num3 = static_cast<uint32_t>(distr(eng));

    uint32_t biased_num = num1 & num2 & num3;
    uint32_t mask = static_cast<uint32_t>(0x807FFFFF); // a zerod exponent
    mask |= biased_num; // add _some_ bits to the exponent
    return int_to_float(num & mask);
}

double get_medium_float_random(std::uniform_int_distribution<unsigned int>& distr, 
        std::mt19937_64& eng) {
    uint32_t num = static_cast<uint32_t>(distr(eng));
    uint32_t num1 = static_cast<uint32_t>(distr(eng));
    uint32_t num2 = static_cast<uint32_t>(distr(eng));
    uint32_t num3 = static_cast<uint32_t>(distr(eng));
    uint32_t num4 = static_cast<uint32_t>(distr(eng));
    uint32_t num5 = static_cast<uint32_t>(distr(eng));
    uint32_t num6 = static_cast<uint32_t>(distr(eng));

    uint32_t biased_num = num1 & num2 & num3;
    uint32_t biased_num2 = num4 | num5 | num6;
    uint32_t mask = static_cast<uint32_t>(0xC07FFFFF); // a zerod exponent
    mask |= biased_num; // add _some_ bits to the exponent
    mask &= biased_num2; // remove _some_ bits from the exponent (including potentially the first bit)
    num |= 0x400000000; // add the first bit to the num to make it "medium"
    return int_to_float(num & mask);
}

double get_large_float_random(std::uniform_int_distribution<unsigned int>& distr, 
        std::mt19937_64& eng) {
    uint32_t num = static_cast<uint32_t>(distr(eng));
    uint32_t mask = static_cast<uint32_t>(0x7F800000); // a zerod exponent
    for (int i = 0; i < 10; i++) {
        uint32_t num1 = static_cast<uint32_t>(distr(eng));
        uint32_t num2 = static_cast<uint32_t>(distr(eng));
        uint32_t num3 = static_cast<uint32_t>(distr(eng));

        uint32_t biased_num = num1 | num2 | num3;
        mask &= biased_num; // remove _some_ bits from the exponent maybe
        auto full = static_cast<uint32_t>(0x7F800000);
        if (((num | mask) & full) != full)
            break; // if we removed at least one bit (so it's not nan), break
    }
    return int_to_float(num | mask);
}

double get_full_double_random(std::uniform_int_distribution<unsigned long long>& distr, std::mt19937_64& eng) {
    return ll_to_double(static_cast<uint64_t>(distr(eng)));
}

double get_smol_double_random(std::uniform_int_distribution<unsigned long long>& distr, 
        std::mt19937_64& eng) {
    uint64_t num = static_cast<uint64_t>(distr(eng));
    uint64_t num1 = static_cast<uint64_t>(distr(eng));
    uint64_t num2 = static_cast<uint64_t>(distr(eng));
    uint64_t num3 = static_cast<uint64_t>(distr(eng));

    uint64_t biased_num = num1 & num2 & num3;
    uint64_t mask = static_cast<uint64_t>(0x800FFFFFFFFFFFFFull); // a zerod exponent
    mask |= biased_num; // add _some_ bits to the exponent
    return ll_to_double(num & mask);
}

double get_medium_double_random(std::uniform_int_distribution<unsigned long long>& distr, 
        std::mt19937_64& eng) {
    uint64_t num = static_cast<uint64_t>(distr(eng));
    uint64_t num1 = static_cast<uint64_t>(distr(eng));
    uint64_t num2 = static_cast<uint64_t>(distr(eng));
    uint64_t num3 = static_cast<uint64_t>(distr(eng));
    uint64_t num4 = static_cast<uint64_t>(distr(eng));
    uint64_t num5 = static_cast<uint64_t>(distr(eng));
    uint64_t num6 = static_cast<uint64_t>(distr(eng));

    uint64_t biased_num = num1 & num2 & num3;
    uint64_t biased_num2 = num4 | num5 | num6;
    uint64_t mask = static_cast<uint64_t>(0xC00FFFFFFFFFFFFFull); // a zerod exponent
    mask |= biased_num; // add _some_ bits to the exponent
    mask &= biased_num2; // remove _some_ bits from the exponent (including potentially the first bit)
    num |= 0x4000000000000000ull; // add the first bit to the num to make it "medium"
    return ll_to_double(num & mask);
}

double get_large_double_random(std::uniform_int_distribution<unsigned long long>& distr, 
        std::mt19937_64& eng) {
    uint64_t num = static_cast<uint64_t>(distr(eng));
    uint64_t mask = static_cast<uint64_t>(0x7FF0000000000000ull); // a zerod exponent
    for (int i = 0; i < 10; i++) {
        uint64_t num1 = static_cast<uint64_t>(distr(eng));
        uint64_t num2 = static_cast<uint64_t>(distr(eng));
        uint64_t num3 = static_cast<uint64_t>(distr(eng));

        uint64_t biased_num = num1 | num2 | num3;
        mask &= biased_num; // remove _some_ bits from the exponent maybe
        auto full = static_cast<uint64_t>(0x7FF0000000000000ull);
        if (((num | mask) & full) != full)
            break; // if we removed at least one bit (so it's not nan), break
    }
    return ll_to_double(num | mask);
}