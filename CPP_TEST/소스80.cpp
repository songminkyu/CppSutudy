#include <iostream>
#include <concepts>

template<class T>
requires (!requires {typename T::difference_type; })
//requires-clause의 부정은 '!' 를 앞에 넣어준다.
void test()
{
	std::cout << "#1" << std::endl;
}

template <class T>
void test() {
	std::cout << "#2" << std::endl;

}

int main()
{
	struct A {
		using difference_type = int;
	};

	test<A>();
	test<int>();
}