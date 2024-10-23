#include <iostream>
#include <type_traits>

/*
template<typename T>
concept C = std::is_arithmetic_v<T>;

C auto add(C auto t1, C auto t2) {
	return t1 + t2;
}

int main() {
	C auto r = add(10.5, 3);
	std::cout << r;
}

*/


template<typename T>
concept C = std::is_arithmetic_v<T>;

template<C T1, C T2>
auto add(T1 t1, T2 t2) {
	return t1 + t2;
}

int main()
{
	auto r = add(10.5, 3);
}
