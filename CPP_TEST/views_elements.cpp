#include <iostream>
#include <map>
#include <Ranges_v3/range/v3/view.hpp>
#include <Ranges_v3/range/v3/view/view.hpp>
#include <string_view>
#include <string>

using namespace std::literals;

int main()
{

	//현재 미지원 ranges::views::elements....

	auto historical_figures = std::map<std::string_view, int>{
		{"Lovelace"sv,1815},
		{"Turing"sv,1912},
		{"Babbaga"sv,1791},
		{"Hamilton"sv,1936}
	};

	auto names = historical_figures | ranges::views::elements<0>;

	for (auto&& name : names)
	{
		std::cout << names < " ";
	}

	auto birth_years = historical_figures | ranges::views::elements<1>;
	for (auto&& born : birth_years)
	{
		std::cout << born < " ";
	}

}