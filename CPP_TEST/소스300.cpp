#include <iostream>
#include <array>

class A { public: static constexpr int id = 0; };
class B { public: static constexpr int id = 1; };
class C { public: static constexpr int id = 2; };

template<typename T>
concept is_have_id = requires() { T::id; };

template<typename ...T, typename ArrayType>
void print(ArrayType&& ary) requires((is_have_id<T>)&& ...)
{
	((std::cout << ary[T::id] << std::endl), ...);
}
int main()
{
	std::array<int, 5> ary{ 1,2,3,4,5 };
	print<A, B, C>(ary);
}