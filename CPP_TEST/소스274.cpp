#include <iostream>
#include <vector>
#include <ranges>

int main() {
	using namespace std::ranges;

	auto until_not_exceed_3 = [](auto p) { return p < 3; };
	std::vector<int> v{ 0,1,2,2,3,1,5 };

	for (auto&& item : v | views::drop(3)) {
		std::cout << item << " ";
	}
	std::cout << "\n";

	for (auto&& item : v | views::drop_while(until_not_exceed_3)) {
		std::cout << item << " ";
	}
	std::cout << "\n";
}