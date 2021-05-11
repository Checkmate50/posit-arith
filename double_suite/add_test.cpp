#include "../src/util.hpp"

#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>
#include <fenv.h>

namespace fs = std::filesystem;

const int RANDOM_COUNT = 1024;

std::string genplus(double d1, double d2) {
    return double_op("\"+\"", d1, d2, d1 + d2);
}

template<typename T>
void generate_rounding_function(std::ofstream& ofile, T f) {
    const int originalRounding = fegetround();
    fesetround(FE_TONEAREST);
    ofile << "rounding_mode = \"TONEAREST\"\n";
    f(ofile);
    fesetround(FE_TOWARDZERO);
    ofile << "rounding_mode = \"TOWARDZERO\"\n";
    f(ofile);
    fesetround(FE_UPWARD);
    ofile << "rounding_mode = \"UPWARD\"\n";
    f(ofile);
    fesetround(FE_DOWNWARD);
    ofile << "rounding_mode = \"DOWNWARD\"\n";
    f(ofile);
    fesetround(originalRounding);
}

template<typename T>
void generate_rounding_function(std::ofstream& ofile, T f, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    const int originalRounding = fegetround();
    fesetround(FE_TONEAREST);
    ofile << "rounding_mode = \"TONEAREST\"\n";
    f(ofile, eng, distr);
    fesetround(FE_TOWARDZERO);
    ofile << "rounding_mode = \"TOWARDZERO\"\n";
    f(ofile, eng, distr);
    fesetround(FE_UPWARD);
    ofile << "rounding_mode = \"UPWARD\"\n";
    f(ofile, eng, distr);
    fesetround(FE_DOWNWARD);
    ofile << "rounding_mode = \"DOWNWARD\"\n";
    f(ofile, eng, distr);
    fesetround(originalRounding);
}

void generate_basics(std::ofstream& ofile) {
    ofile << genplus(1., 1.);
    ofile << genplus(1., 2.);
    ofile << genplus(2., 1.);
    ofile << genplus(-1., 1.);
    ofile << genplus(1., -1.);
    ofile << genplus(-1., -2.);
    ofile << genplus(-.2, -.1);
    ofile << genplus(.10001, .1);
    ofile << genplus(.10001, -.1000001);
    ofile << genplus(.1000000000000000001, .10000000000000001); // actually equal
    ofile << genplus(-.01, -.011);
    ofile << genplus(100.123, -100.124); // some rounding required
    ofile << genplus(123.321, 123.321);
    ofile << genplus(-123.3211, 123.321);
    ofile << genplus(1.001e64, -1e64); // big lads
    ofile << genplus(1.001e-64, 1e-64); // smol lads
    ofile << genplus(-1.001e-64, -1e-64);
    ofile << '\n';
}

void generate_rounding_basics(std::ofstream& ofile) {
    generate_rounding_function(ofile, generate_basics);
}

void generate_exceptionals(std::ofstream& ofile) {
    ofile << genplus(0., 0.);
    ofile << genplus(-0., 0.); // -0 shenanigans
    ofile << genplus(.1, -0.);

    ofile << genplus(get_double_inf(), get_double_inf()); // infinity shenanigans
    ofile << genplus(get_double_neginf(), get_double_inf());
    ofile << genplus(get_double_inf(), get_double_neginf());
    ofile << genplus(get_double_neginf(), get_double_inf());

    ofile << genplus(get_double_max(), get_double_min()); // minimum/maximum
    ofile << genplus(get_double_max(), get_double_inf());
    ofile << genplus(get_double_min(), get_double_neginf());
    ofile << genplus(get_double_max(), get_double_max());
    ofile << genplus(get_double_min(), -get_double_min());

    ofile << genplus(get_double_nan(), get_double_nan()); // basic nan
    ofile << genplus(get_double_nan(), get_double_inf());
    ofile << genplus(get_double_nan(), get_double_neginf());
    ofile << genplus(get_double_nan(), -0.);

    ofile << genplus(ll_to_double(0xFFFFFFFFFFFFFFFFull), ll_to_double(0xFFFFFFFFFFFFFFFFull)); // stupid nan encodings
    ofile << genplus(ll_to_double(0x7FFFFFFFFFFFFFFFull), ll_to_double(0xFFFFFFFFFFFFFFFFull));
    ofile << genplus(ll_to_double(0xFFFFFFFFFFFFFFFFull), get_double_inf());
    ofile << genplus(ll_to_double(0x7FFFFFFFFFFFFFFFull), ll_to_double(0x3FFFFFFFFFFFFFFFull));
    ofile << genplus(ll_to_double(0x8000000000000000ull), 0); // I think this is just -0, but let's check (it is!)

    ofile << '\n';
}

void generate_rounding_exceptionals(std::ofstream& ofile) {
    generate_rounding_function(ofile, generate_exceptionals);
}

void generate_full_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genplus(get_full_double_random(distr, eng), get_full_double_random(distr, eng));
    ofile << '\n';
}

void generate_rounding_full_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_rounding_function(ofile, generate_full_random, eng, distr);
}

void generate_smol_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genplus(get_smol_double_random(distr, eng), get_smol_double_random(distr, eng));
    ofile << '\n';
}

void generate_rounding_smol_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_rounding_function(ofile, generate_smol_random, eng, distr);
}

void generate_medium_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genplus(get_medium_double_random(distr, eng), get_medium_double_random(distr, eng));
    ofile << '\n';
}

void generate_rounding_medium_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_rounding_function(ofile, generate_medium_random, eng, distr);
}

void generate_large_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genplus(get_large_double_random(distr, eng), get_large_double_random(distr, eng));
    ofile << '\n';
}

void generate_rounding_large_random(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_rounding_function(ofile, generate_large_random, eng, distr);
}

int main() {
    try {
        if (!fs::is_directory("../test_bin") || !fs::exists("../test_bin")) { // Check if src folder exists
            fs::create_directory("../test_bin"); // create src folder
        }
        std::ofstream ofile;
        ofile.open("../test_bin/double_add_test.py");
        {
            ofile << get_python_header();
            generate_rounding_basics(ofile);
            generate_rounding_exceptionals(ofile);
            auto eng = setup_random();
            std::uniform_int_distribution<unsigned long long> distr;
            generate_rounding_full_random(ofile, eng, distr);
            generate_rounding_smol_random(ofile, eng, distr);
            generate_rounding_medium_random(ofile, eng, distr);
            generate_rounding_large_random(ofile, eng, distr);
        }
        ofile.close();
        std::cout << "add_test SUCCESS" << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "add_test FAILED" << std::endl;
        std::cout << ex.what() << std::endl;
    }
}