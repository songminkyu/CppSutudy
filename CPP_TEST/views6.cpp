
#include <string>
#include <Ranges_v3/range/v3/range.hpp>
#include <Ranges_v3/range/v3/view.hpp>
#include <iostream>
#include <vector>

/*

Print all the elements of a range in reverse order:

*/
int main()
{
	std::vector<int> v{ 1,1,2,3,5,8,13,21,34 };

	auto print_elem = [](auto const e) {std::cout << e << '\n'; };


	std::for_each(
		std::crbegin(v), std::crend(v),
		print_elem);

	// or

	for (auto const i : v | ranges::views::reverse)
	{
		print_elem(i);
	};
}