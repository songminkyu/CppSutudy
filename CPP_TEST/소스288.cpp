#include <iostream>

/*

Cute C++ trick of the day: you can iterate backwards through a parameter pack by folding over a right-associative operator (like assignment, for instance) https://godbolt.org/z/h5P1Mxsrz
오전 8:43 · 2021년 4월 7일·Twitter Web

*/
template <class...Ts>
void print_args_backwrads(Ts... ts)
{
	auto print_one = [](auto t) {
		std::cout << t << std::endl;
		return std::type_identity<void>{};
	};

	(print_one(ts) = ...);//backwrads	
}

template <class...Ts>
void print_args_forwards(Ts... ts)
{
	auto print_one = [](auto t) {
		std::cout << t << std::endl;
		return std::type_identity<void>{};
	};
	
	(print_one(ts), ...);//forwards
}

int main()
{
	print_args_backwrads(1, 2, "hello", 3, 4, "world");

	std::cout << "################################################" << std::endl;

	print_args_forwards(1, 2, "hello", 3, 4, "world");
}