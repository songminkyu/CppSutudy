#include <string>
#include <vector>
#include <Ranges_v3/range/v3/range.hpp>
#include <Ranges_v3/range/v3/iterator.hpp>
#include <Ranges_v3/range/v3/view.hpp>
#include <iostream>

/*

Print the Roman numeral of the last three numbers divisible to 7 in
the range [101, 200], in reverse order.
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
	
	auto v = ranges::iota_view(101, 201)
		| ranges::views::reverse
		| ranges::views::filter([](auto v) {return v % 7 == 0; })
		| ranges::views::transform(to_roman)
		| ranges::views::take(3)
		| ranges::to_vector;
	
	for (auto && FromVector : v)
	{
		std::cout << FromVector << std::endl;
	}

}