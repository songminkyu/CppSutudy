#include <string>
#include <vector>
#include <Ranges_v3/range/v3/range.hpp>
#include <Ranges_v3/range/v3/view.hpp>
#include <iostream>



/*
    https://mariusbancila.ro/blog/2019/01/20/cpp-code-samples-before-and-after-ranges/
*/
/*

Print all the Roman numerals from 101 to 200. To convert a number to 
its corresponding Roman numeral the function to_roman() shown ealier is used.

*/
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

	auto print_elem = [](auto const e) {std::cout << e << '\n'; };


	for (auto n : ranges::iota_view(101, 201)
		| ranges::views::transform(to_roman))
	{
		print_elem(n);
	}
}