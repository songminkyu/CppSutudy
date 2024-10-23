#include <iostream>
#include <concepts>

/*
concepts 간략 구문은 아니지만
concpets의 hello world 코딩은 이 정도로~
*/
template <typename T, typename U>
concept can_add = requires(T t, U u) { t + u; };

template <typename T, typename U> requires can_add<T,U>
auto add(T t, U u)
{
	return t + u;
}

int main()
{
	auto p = add(10, 14.5);
	std::cout << p << std::endl;	
}