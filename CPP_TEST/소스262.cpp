#include <algorithm>
#include <ranges>
#include <iostream>
#include <vector>
int main()
{
	std::vector<int> vec{ 1,2,3 };
	std::distance(begin(vec), end(vec));

	using namespace std::ranges;
	distance(begin(vec), end(vec));
}
