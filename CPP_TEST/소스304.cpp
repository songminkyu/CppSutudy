#include <iostream>
#include <concepts>

template<class T>
struct A {
	void test() { std::cout << "#1\n"; }
};

template<class T> requires requires(T a) { a.test1(); }
struct A<T> {
	void test() { std::cout << "#2\n"; }
};

template<class T>requires requires(T a) { a.test2(); }
struct A<T> {
	void test() { std::cout << "#3\n"; }
};

struct A1 { void test1(); };
struct A2 { void test2(); };
struct A3 {};

int main() {
	A<A1> a1{};
	a1.test();

	A<A2> a2{};
	a2.test();

	A<A3> a3{};
	a3.test();

	return EXIT_SUCCESS;
}
