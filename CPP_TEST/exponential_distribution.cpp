#include <iostream>
#include <random>
#include <array>
using namespace std;

int main()
{
	//exponential_distribution 클래스를 사용한 예

	array<int, 10> tmp = { 0, };

	std::random_device seed_gen;

	std::default_random_engine eng(seed_gen());

	std::exponential_distribution<> dist(1);

	for (int i = 0; i < 100000; ++i) {

		double number = dist(eng);

		if (number < 1.0) ++tmp[int(10 * number)];
	}

	for (const auto& ed : tmp)
	{
		std::cout << ed << std::endl;
	}
}