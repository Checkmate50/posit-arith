#pragma once

#include <string>
#include <random>

std::string get_float_bits(float f);
std::string get_double_bits(double d);
float int_to_float(uint32_t i);
double ll_to_double(uint64_t l);

float get_float_inf();
float get_float_neginf();
float get_float_nan();
float get_float_max();
float get_float_min();

double get_double_inf();
double get_double_neginf();
double get_double_nan();
double get_double_max();
double get_double_min();

std::mt19937_64 setup_random();
double get_full_float_random(std::uniform_int_distribution<unsigned int>& distr, 
        std::mt19937_64& eng); // Fully random floats
double get_smol_float_random(std::uniform_int_distribution<unsigned int>& distr, 
        std::mt19937_64& eng); // smol lads
double get_medium_float_random(std::uniform_int_distribution<unsigned int>& distr,
        std::mt19937_64& eng); // Realistically sized floats
double get_large_float_random(std::uniform_int_distribution<unsigned int>& distr, 
        std::mt19937_64& eng); // Extremely large floats (nans mostly excluded)

double get_full_double_random(std::uniform_int_distribution<unsigned long long>& distr, 
        std::mt19937_64& eng); // Fully random doubles
double get_smol_double_random(std::uniform_int_distribution<unsigned long long>& distr, 
        std::mt19937_64& eng); // smol lads
double get_medium_double_random(std::uniform_int_distribution<unsigned long long>& distr, 
        std::mt19937_64& eng); // Realistically sized doubles
double get_large_double_random(std::uniform_int_distribution<unsigned long long>& distr, 
        std::mt19937_64& eng); // Extremely large doubles (nans mostly excluded)

std::string get_python_header();
std::string float_op(std::string op, float f, float result);
std::string float_op(std::string op, float f1, float f2, float result);
std::string float_comp(std::string op, float f, bool result);
std::string float_comp(std::string op, float f1, float f2, bool result);
std::string double_op(std::string op, double d, double result);
std::string double_op(std::string op, double d1, double d2, double result);
std::string double_comp(std::string op, double d, bool result);
std::string double_comp(std::string op, double d1, double d2, bool result);