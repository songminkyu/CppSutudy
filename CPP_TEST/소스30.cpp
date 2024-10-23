#include <iostream>
#include "pipes/pipes.hpp"
#include <string>
int main()
{
	auto const inputs1 = std::vector<int>{ 1, 2, 3 };
	auto const inputs2 = std::vector<std::string>{ "up", "down", "left"};

	auto results = std::vector<std::string>{};

	pipes::cartesian_product(inputs1, inputs2)
		>>= pipes::transform([](int i, std::string const& s) { return std::to_string(i) + '-' + s; })
		>>= pipes::push_back(results);


	for (const auto & i : results)
	{
		std::cout << i << std::endl;
	}
}