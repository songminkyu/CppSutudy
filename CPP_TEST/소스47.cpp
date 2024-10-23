#include <iostream>
#include <type_traits>

template<typename T>
concept C = std::is_arithmetic_v<T>;


template<C T1,C T2> requires(sizeof(T1) >= sizeof(T2))
auto add(T1 t1, T2 t2) requires (sizeof(t1 + t2) > sizeof(int))
{
	return t1 + t2;
}

int main()
{
	auto r = add(10.51, 3.5f);
}