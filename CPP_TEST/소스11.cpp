#include <iostream>

template< auto z >
struct A {
	void print() {
		std::cout << z << std::endl;
	}
};

int main() {
	A<13> a;
	a.print();
}