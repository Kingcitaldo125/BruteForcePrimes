#include <iostream>
#include <fstream>
#include <chrono>

#include "primes.h"

using std::cout;
using std::endl;

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

