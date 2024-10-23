#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
	int a[] = { 1,2,3 };
	std::vector<int> data{ 10,20 };

	using namespace std::ranges;
	copy(a, std::inserter(data, ++std::begin(data)));
	for (auto&& item : data) std::cout << item << " ";
}