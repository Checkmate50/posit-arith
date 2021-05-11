#include "../src/util.hpp"

#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>

namespace fs = std::filesystem;

const int RANDOM_COUNT = 1024;

std::string genop(std::string op, float d1, float d2) {
    float result;
    if (op == "==")
        result = d1 == d2;
    else if(op == "<")
        result = d1 < d2;
    else if(op == ">")
        result = d1 > d2;
    else if(op == "<=")
        result = d1 <= d2;
    else if(op == ">=")
        result = d1 >= d2;
    return float_comp('\"' + op + '\"', d1, d2, result);
}

std::string genop(std::string op, double d1, double d2) {
    double result;
    if (op == "==")
        result = d1 == d2;
    else if(op == "<")
        result = d1 < d2;
    else if(op == ">")
        result = d1 > d2;
    else if(op == "<=")
        result = d1 <= d2;
    else if(op == ">=")
        result = d1 >= d2;
    return double_comp('\"' + op + '\"', d1, d2, result);
}

void generate_basics(std::string op, std::ofstream& ofile) {
    ofile << genop(op, 1., 1.);
    ofile << genop(op, 1., 2.);
    ofile << genop(op, 2., 1.);
    ofile << genop(op, -1., 1.);
    ofile << genop(op, 1., -1.);
    ofile << genop(op, -1., -2.);
    ofile << genop(op, -.2, -.1);
    ofile << genop(op, .10001, .1);
    ofile << genop(op, .10001, .1000001);
    ofile << genop(op, .1000000000000000001, .10000000000000001); // actually equal
    ofile << genop(op, -.01, -.011);
    ofile << genop(op, -100.123, -100.124); // some rounding required
    ofile << genop(op, 123.321, 123.321);
    ofile << genop(op, 123.3211, 123.321);
    ofile << genop(op, 1.001e64, 1e64); // big lads
    ofile << genop(op, 1.001e-64, 1e-64); // smol lads
    ofile << genop(op, -1.001e-64, -1e-64);
    ofile << '\n';
}

void generate_all_basics(std::ofstream& ofile) {
    generate_basics("==", ofile);
    generate_basics("<", ofile);
    generate_basics(">", ofile);
    generate_basics("<=", ofile);
    generate_basics(">=", ofile);
}

void generate_exceptionals(std::string op, std::ofstream& ofile) {
    ofile << genop(op, 0., 0.);
    ofile << genop(op, -0., 0.); // -0 shenanigans
    ofile << genop(op, -0., -0.);

    ofile << genop(op, get_double_inf(), get_double_inf()); // infinity shenanigans
    ofile << genop(op, get_double_neginf(), get_double_inf());
    ofile << genop(op, get_double_inf(), get_double_neginf());
    ofile << genop(op, get_double_neginf(), get_double_inf());

    ofile << genop(op, get_double_max(), get_double_min()); // minimum/maximum
    ofile << genop(op, get_double_max(), get_double_inf());
    ofile << genop(op, get_double_min(), get_double_neginf());

    ofile << genop(op, get_double_nan(), get_double_nan()); // basic nan
    ofile << genop(op, get_double_nan(), get_double_inf());
    ofile << genop(op, get_double_nan(), get_double_neginf());
    ofile << genop(op, get_double_nan(), -0.);

    ofile << genop(op, ll_to_double(0xFFFFFFFFFFFFFFFFull), ll_to_double(0xFFFFFFFFFFFFFFFFull)); // stupid nan encodings
    ofile << genop(op, ll_to_double(0x7FFFFFFFFFFFFFFFull), ll_to_double(0xFFFFFFFFFFFFFFFFull));
    ofile << genop(op, ll_to_double(0xFFFFFFFFFFFFFFFFull), get_double_inf());
    ofile << genop(op, ll_to_double(0x7FFFFFFFFFFFFFFFull), ll_to_double(0x3FFFFFFFFFFFFFFFull));
    ofile << genop(op, ll_to_double(0x8000000000000000ull), 0); // I think this is just -0, but let's check (it is!)

    ofile << '\n';
}

void generate_all_exceptionals(std::ofstream& ofile) {
    generate_exceptionals("==", ofile);
    generate_exceptionals("<", ofile);
    generate_exceptionals(">", ofile);
    generate_exceptionals("<=", ofile);
    generate_exceptionals(">=", ofile);
}

void generate_full_random(std::string op, std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genop(op, get_full_double_random(distr, eng), get_full_double_random(distr, eng));
    ofile << '\n';
}

void generate_full_random_all(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_full_random("==", ofile, eng, distr);
    generate_full_random("<", ofile, eng, distr);
    generate_full_random(">", ofile, eng, distr);
    generate_full_random("<=", ofile, eng, distr);
    generate_full_random(">=", ofile, eng, distr);
}

void generate_smol_random(std::string op, std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genop(op, get_smol_double_random(distr, eng), get_smol_double_random(distr, eng));
    ofile << '\n';
}

void generate_smol_random_all(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_smol_random("==", ofile, eng, distr);
    generate_smol_random("<", ofile, eng, distr);
    generate_smol_random(">", ofile, eng, distr);
    generate_smol_random("<=", ofile, eng, distr);
    generate_smol_random(">=", ofile, eng, distr);
}

void generate_medium_random(std::string op, std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genop(op, get_medium_double_random(distr, eng), get_medium_double_random(distr, eng));
    ofile << '\n';
}

void generate_medium_random_all(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_medium_random("==", ofile, eng, distr);
    generate_medium_random("<", ofile, eng, distr);
    generate_medium_random(">", ofile, eng, distr);
    generate_medium_random("<=", ofile, eng, distr);
    generate_medium_random(">=", ofile, eng, distr);
}

void generate_large_random(std::string op, std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    
    for (int i = 0; i < RANDOM_COUNT; i++)
        ofile << genop(op, get_large_double_random(distr, eng), get_large_double_random(distr, eng));
    ofile << '\n';
}

void generate_large_random_all(std::ofstream& ofile, std::mt19937_64& eng,
        std::uniform_int_distribution<unsigned long long>& distr) {
    generate_large_random("==", ofile, eng, distr);
    generate_large_random("<", ofile, eng, distr);
    generate_large_random(">", ofile, eng, distr);
    generate_large_random("<=", ofile, eng, distr);
    generate_large_random(">=", ofile, eng, distr);
}

int main() {
    try {
        if (!fs::is_directory("../test_bin") || !fs::exists("../test_bin")) { // Check if src folder exists
            fs::create_directory("../test_bin"); // create src folder
        }
        std::ofstream ofile;
        ofile.open("../test_bin/double_comp_test.py");
        {
            ofile << get_python_header();
            generate_all_basics(ofile);
            generate_all_exceptionals(ofile);
            auto eng = setup_random();
            std::uniform_int_distribution<unsigned long long> distr;
            generate_full_random_all(ofile, eng, distr);
            generate_smol_random_all(ofile, eng, distr);
            generate_medium_random_all(ofile, eng, distr);
            generate_large_random_all(ofile, eng, distr);
        }
        ofile.close();
        std::cout << "comp_test SUCCESS" << std::endl;
    } catch (const std::exception& ex) {
        std::cout << "comp_test FAILED" << std::endl;
        std::cout << ex.what() << std::endl;
    }
}