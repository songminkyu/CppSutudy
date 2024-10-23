#include <iostream>

template<class T>
struct S {
	T data1 = {};
	T data2 = {};
};

template< class T > S(T)->S<T>;
template< class T1, class T2 > S(T1 a, T2 b)->S<decltype(true ? a : b)>;

int main()
{
	S a1{ 1 };
	S a2{ 1, 3.14 };

	std::cout << typeid(a1).name() << std::endl;
	std::cout << typeid(a2).name() << std::endl;
}