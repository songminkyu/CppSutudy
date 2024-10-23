#include <Ranges_v3/range/v3/range.hpp>
#include <Ranges_v3/range/v3/view.hpp>
#include <iostream>


int main()
{
	auto even = [](int i) {return 0 == i % 2; };

	for (auto&& item : ranges::views::iota(1)
		| ranges::views::filter(even)
		| ranges::views::take(13))
	{
		std::cout << item << std::endl;
	}

}