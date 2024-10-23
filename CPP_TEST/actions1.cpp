#include <vector>
#include <Ranges_v3/range/v3/action.hpp>
#include <iostream>
#include <string>

int main()
{
	std::vector<int> v{ 21, 1, 3, 8, 13, 1, 5, 2 };

	v = std::move(v) |
		ranges::actions::sort |
		ranges::actions::unique |
		ranges::actions::reverse;


	for (auto&& i : v)
	{
		std::cout << i << std::endl;
	}
}
