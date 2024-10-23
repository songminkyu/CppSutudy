#include <iostream>

template<class... Ts>
struct A : Ts...{
	using Ts::operator()...;
	A(Ts... args) :Ts{ args }... {};
};

int main() {
	A a{
		[](int) {std::cout << "int\n"; },
		[](float) {std::cout << "float\n"; },
		[](auto) {std::cout << "others\n"; }
	};

	a(10); a(13.f); a("test");
}