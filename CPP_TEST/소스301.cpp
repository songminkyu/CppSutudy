#include <iostream>
#include <array>

class A {

public:
	static constexpr std::size_t   size = 14;
	static constexpr std::uint8_t  layer = 1;
};
class B {

public:
	static constexpr std::size_t   size = 26;
	static constexpr std::uint8_t  layer = 2;
};
class C {

public:
	static constexpr std::size_t   size = 32;
	static constexpr std::uint8_t  layer = 3;
};

template<typename T>
concept is_have_layer = requires() { T::size; };

template<typename ...T, typename ArrayType>
void print(ArrayType&& ary) requires((is_have_layer<T>)&& ...)
{
	((std::cout << ary[T::size] << std::endl), ...);
}
int main()
{
	std::array<std::size_t, 3> ary{ 1,2,3 };
	print<A, B, C>(ary);
}