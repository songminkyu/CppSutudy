#include <iostream>

struct A {
	void print() const { std::cout << "A" << std::endl; }
};

struct B {
	void print() const { std::cout << "B" << std::endl; }
};

template<class... Baseclass>
struct Mixin : Baseclass...{
	void print()const {
		(Baseclass::print(), ...);
		std::cout << "Mix" << std::endl;
	}
};

int main()
{
	Mixin<A, B> ab{};
	ab.print();
	return 0;
}