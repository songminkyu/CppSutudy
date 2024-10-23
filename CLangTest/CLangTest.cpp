#include <iostream>
#include <utility>
#include <array>

template<std::size_t INDEX, typename T, std::size_t N>
requires(N > INDEX)
T& get(T(&t)[N]) {
	return t[INDEX];
}


int main() {
	//std::array<int, 4> a { 1,2,3,4 };
	int a[]{ 1,2,3,4 };
	std::cout << get<0>(a) << std::endl;
	get<0>(a) = 100;
	std::cout << get<0>(a) << std::endl;
	std::cout << get<3>(a) << std::endl;
}