#include <iostream>
#include <tuple>

/*
std namespace에 새로운 declaration이나 definition를 추가하거나 std 내부에 새로운 
namespace를 만드는 것은 undefined behavior에 속한다.

하지만 std 내부에 프로그래머가 기존 요구 조건을 만족한다면 class template에 대한
template specialization를 임의로 추가하는 것을 허용한다.

두번째 스샷 예제가 적법한 이유!!
*/


struct A
{
protected:
	int a = 1;
	int b = 2;
};
struct MyStruct : A {
protected:
	int c = 3;
	int d = 4;
public:
	template<std::size_t N>
	decltype(auto) get() const {
		
		if constexpr (N == 0) return a;
		else if constexpr (N == 1) return b;
		else if constexpr (N == 2) return c;
		else if constexpr (N == 3) return d;

	}
};

namespace std {
	template<>
	struct tuple_size<MyStruct> : std::integral_constant<std::size_t, 4> {};
	template<std::size_t N>
	struct tuple_element<N, MyStruct> {
		using type = decltype(std::declval<MyStruct>().get<N>());
	};
}
int main()
{
	MyStruct z{};
	auto [a, b, c, d] = z;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
}