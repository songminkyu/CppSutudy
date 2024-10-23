#include <iostream>
#include <random>
#include <array>
#include <map>
using namespace std;

int main()
{
	array<int, 20> tmp = { 0, };

	std::random_device seed_gen;

	std::default_random_engine eng(seed_gen());

	std::poisson_distribution<> dist(3.5);

	for (int i = 0; i < 100000; ++i) {

		int t = dist(eng);

		++tmp[t];

		if (t > 19) continue;

	}

	std::random_device rd;
	std::mt19937 gen(rd());

	// if an event occurs 4 times a minute on average
	// how often is it that it occurs n times in one minute?
	std::poisson_distribution<> d(4);

	std::map<int, int> hist;
	for (int n = 0; n < 10000; ++n) {
		++hist[d(gen)];
	}
	for (auto p : hist) {
		std::cout << p.first <<
			' ' << std::string(p.second / 100, '*') << '\n';
	}
}