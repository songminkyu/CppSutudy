#include <iostream>
#include <concepts>


template< class U > 
concept integral = std::is_integral_v<U>;

template < class U >
concept floating = std::is_floating_point_v<U>;

struct A {
	template <class T, class D = int>
	struct S {
		T Data;
	};

	template<integral U> S(U)->S<long long int>;
	template<floating U> S(U)->S<double>;
};

int main()
{
	A::S a{ 10 };
	A::S b{ 15.5 };

	std::cout << typeid(a).name() << std::endl;
	std::cout << typeid(b).name() << std::endl;

	std::cout << a.Data << std::endl;

}