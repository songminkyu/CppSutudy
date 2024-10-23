#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
	int a[] = { 1,2,3 };
	std::vector<int> data;

	using namespace std::ranges;
	copy(a, std::back_inserter(data));
	for (auto&& item : data) std::cout << item << " ";
}