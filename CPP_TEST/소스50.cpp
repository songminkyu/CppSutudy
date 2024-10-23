#include <iostream>
#include <type_traits>
#include <concepts>

/*
GCC 10에 concepts이 구현되어가고 있다. 이미 컴파일이 되고, concepts core 
부분과 라이브러리를 구현하고 있는 msvc를 넘어 concepts 편이 
문법까지 이미 구현된 상태.
*/
template<typename T> concept C1 = true;
template<typename T> concept C2 = true;
template<typename... Ts> concept C3 = true;

void g1(const C1 auto*, C2 auto&) {};
void g2(C1 auto&...) {};
void g3(C3 auto...) {};
void g4(C3 auto) {};

auto add(auto a, auto b) { return a + b; }
template<typename T, typename U> concept ltest = std::same_as<T, U>;

template<ltest<int> A>
struct Test{};

int main() {
	auto z = add(1, 2);
	std::cout << z;

	Test<int> a;
}