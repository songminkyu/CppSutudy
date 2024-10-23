#include <Ranges_v3/range/v3/range.hpp>
#include <Ranges_v3/range/v3/view.hpp>
#include <iostream>


int main()
{
	unsigned int numbers[10] = { 0,1,2,3,4,5,6,7,8,9 };
	auto evennumbers = numbers | ranges::views::filter([](int n) { return n % 2 == 0; })
		| ranges::views::transform([](int n) {return n * 2; })
		| ranges::views::transform([](int n) {return n + 100; })
		| ranges::views::reverse;

	std::cout << evennumbers << std::endl;
}