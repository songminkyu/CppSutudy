
#include <vector>
#include <Ranges_v3/range/v3/range.hpp>
#include <Ranges_v3/range/v3/action.hpp>
#include <iostream>
#include <string>
#include <stdio.h>


std::string to_roman(int value)
{
	std::vector<std::pair<int, char const*>> roman
	{
	   { 1000, "M" },{ 900, "CM" },
	   { 500, "D" },{ 400, "CD" },
	   { 100, "C" },{ 90, "XC" },
	   { 50, "L" },{ 40, "XL" },
	   { 10, "X" },{ 9, "IX" },
	   { 5, "V" },{ 4, "IV" },
	   { 1, "I" }
	};

	std::string result;
	for (auto const& [d, r] : roman)
	{
		while (value >= d)
		{
			result += r;
			value -= d;
		}
	}

	return result;
}

int main()
{

	std::vector<int> ints{ 1,1,2,3,5,8,13,21,34 };
	auto even = [](int i) { return 0 == i % 2; };
	auto square = [](int i) { return i * i; };
	
	for (int i : ints | ranges::views::filter(even) | ranges::views::transform(square)) {
		std::cout << i << ' ';
	}	

	std::cout << "\n";

	
	auto print_elem = [](auto const e) {std::cout << e << '\n'; };

	auto is_even = [](auto const i) {return i % 2 == 0; };

	for (auto const i : ints
		| ranges::views::drop(2)
		| ranges::views::take(3)
		| ranges::views::filter(is_even))
	{
		print_elem(i);
	};

}