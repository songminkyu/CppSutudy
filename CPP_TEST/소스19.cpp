#include <iostream>
struct A { int a = 10; };
struct B :A { int b = 20; };
struct C :B { int c = 30; };

int main() {
	C c{ {1,2}, 3 };
	std::cout << c.a << "," << c.b << "," << c.c << std::endl;
}
