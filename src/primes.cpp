#include <iostream>
#include <thread>
#include <mutex>

#include "primes.h"

static std::mutex mtx;

constexpr bool divisible(const unsigned int i)
{
	if (i % 2 == 0)
		return true;

	for(unsigned int asdf = 3; asdf < i; ++asdf)
	{
		if (i % asdf == 0)
			return true;
	}

	return false;
}


std::vector<unsigned int> threaded_primes(
	std::vector<unsigned int>& retv,
	const unsigned int start_number,
	const unsigned int end_number)
{
	std::vector<unsigned int> local_primes;
	for (unsigned int i = start_number; i < end_number; ++i)
	{
		if (!divisible(i))
			local_primes.push_back(i);
	}

	{
		std::lock_guard<std::mutex> lock(mtx);
		for (auto& item : local_primes)
		{
			retv.push_back(item);
		}
	}

	return local_primes;
}


std::vector<unsigned int> n_primes(const unsigned int N, const int n_threads)
{
	unsigned int start_number = 2;
	unsigned int primes_per_thread = N / n_threads;
	std::cout << "primes_per_thread: " << primes_per_thread << std::endl;
	unsigned int end_number = (start_number + primes_per_thread) - start_number;

	std::vector<unsigned int> retv{ 2 };
	std::vector<std::thread> threads;

	for (int i = 0; i < n_threads; ++i)
	{
		threads.emplace_back(
			std::thread(
				threaded_primes,
				std::ref(retv),
				start_number,
				end_number)
		);

		start_number = end_number + 1;
		end_number += primes_per_thread;
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	return retv;
}

