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
	std::vector<std::string> words{
		"Lorem", " ", "ipsum", " ",
		"dolor", " ", "sit", " ",
		"amet" };

	std::string text = words |
		ranges::move |
		ranges::actions::join;

	std::cout << text.c_str() << std::endl;

}