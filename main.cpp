#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;

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


std::vector<unsigned int> n_primes(const unsigned int N, const int n_threads = 1)
{
	unsigned int start_number = 2;
	unsigned int primes_per_thread = N / n_threads;
	cout << "primes_per_thread: " << primes_per_thread << endl;
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


int main(int argc, char** argv)
{
	//bool write_to_disk = true;
	bool write_to_disk = false;

	const int n_threads = 2;

	cout << "Calculating using " << n_threads << (n_threads == 1 ? " thread..." : " threads...") << endl;
	std::chrono::steady_clock::time_point sclock1 = std::chrono::steady_clock::now();
	auto vector = n_primes(100'000, n_threads);
	std::chrono::steady_clock::time_point sclock2 = std::chrono::steady_clock::now();
	cout << "Done." << endl;

	cout << "Took '" << std::chrono::duration_cast<std::chrono::seconds>(sclock2 - sclock1).count() << "' seconds" << endl;

	if (write_to_disk)
	{
		std::ofstream off("out.txt", std::ofstream::out);

		cout << "Writing to disk..." << endl;
		for (const auto& i : vector)
		{
			off << i << endl;
		}
		cout << "Done." << endl;
		off.flush();
		off.close();
	}

	return 0;
}
