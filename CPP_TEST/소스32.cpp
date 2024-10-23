#include <iostream>

template <typename ...Args>
struct A {
	alignas(Args...) char buffer[1024];
};

int main()
{
	A<int, char, double> a{};
	/*std::cout << sizeof(a.buffer) << std::endl;
	std::cout << alignof(decltype(a)) << std::endl;*/
}