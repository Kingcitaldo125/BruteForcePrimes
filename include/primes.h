#pragma once

#include <vector>

constexpr bool divisible(const unsigned int i);
std::vector<unsigned int> threaded_primes(std::vector<unsigned int>& retv, const unsigned int start_number, const unsigned int end_number);
std::vector<unsigned int> n_primes(const unsigned int N, const int n_threads = 1);

