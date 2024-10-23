#include <iostream>

struct Bagel {
	int x = 0;
	void func() {
		//...
		//OK until C++20. Warning in C++20.
		[=]() { std::cout << x; }();

		//Error/warning until C++20. OK in C++20.
		[=, this]() { std::cout << x; }();
	}
};

int main()
{
	Bagel b;
	b.x = 2;
	b.func();
}