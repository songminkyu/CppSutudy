#include <vector>
#include <Ranges_v3/range/v3/action.hpp>
#include <Ranges_v3/range/v3/range.hpp>
#include <iostream>

/*
Remove the smallest two and the largest two values of a 
range and retain the other ones, ordered, in a second range.
*/
int main()
{
	std::vector<int> v{ 21, 1, 3, 8, 13, 1, 5, 2 };
	auto v2 = v |
		ranges::copy |
		ranges::actions::sort |
		ranges::actions::slice(2, ranges::end - 2);


	for (auto && FromV : v2)
	{
		std::cout << FromV << std::endl;
	}
}