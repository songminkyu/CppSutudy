
#include <iostream>
#include <vector>
#include <type_traits>


/* consteval를 추가함으로써 컴파일 시간에만 행렬값을 구할 수도~*/
template<class T, auto M, auto N> constexpr auto determinant(T const(&vals)[M][N])
requires (M == 2 && N == 2)
{
	return vals[0][0] * vals[1][1] - vals[0][1] * vals[1][0];
}

/*
gcc 가 먼저 구현 됫으나, 추후 msvc 적용되면 컴파일이 가능 할듯. 현재 constexpr 로 대체
*/
//
///* consteval를 추가함으로써 컴파일 시간에만 행렬값을 구할 수도~*/
//template<class T, auto M, auto N> consteval auto determinant(T const(&vals)[M][N])
//requires (M == 2 && N == 2)
//{
//	return vals[0][0] * vals[1][1] - vals[0][1] * vals[1][0];
//}
//

int main() {
	auto del
		= determinant({
			{1,2},
			{3,4}
			});
	std::cout << del;
}