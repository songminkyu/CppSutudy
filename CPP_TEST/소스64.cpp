#include <iostream>
#include <vector>
#include <type_traits>
//#include <concepts>

template<class T, auto M, auto N> auto determinant(T const(&vals)[M][N])
requires (M == 2 && N == 2)
{
	return vals[0][0] * vals[1][1] - vals[0][1] * vals[1][0];
}

int main() {
	auto del
		= determinant({
			{1,2},
			{3,4}
			});
	std::cout << del;
}