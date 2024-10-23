#include <string>
#include <Ranges_v3/range/v3/range.hpp>
#include <Ranges_v3/range/v3/view.hpp>
#include <iostream>

/*
Count the number of words (as delimited by space) in a text.

*/

int main()
{

	auto text = "Lorem ipsum dolor sit amet";

	auto count = ranges::distance(
		ranges::views::c_str(text) | ranges::views::split(' '));


	std::cout <<"count : "<< count << std::endl;
}