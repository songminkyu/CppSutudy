#include <iostream>
#include <type_traits>

template<typename T> concept INTEGRAL = std::is_integral_v<T>;
template<typename T> concept FLOATING = std::is_floating_point_v<T>;
template<typename T> concept ARITHMETIC = INTEGRAL<T> || FLOATING<T>;

template<ARITHMETIC T>
struct A
{
	void call() requires INTEGRAL<T> {std::cout << "int call" << std::endl; }
	void call() requires FLOATING<T> {std::cout << "float call" << std::endl; }
};


int main()
{
	A<int> a1{};
	a1.call();

	A<double> a2{};
	a2.call();


}
