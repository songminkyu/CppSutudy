#include <iostream>
#include <functional>

int add(int a, int b, int c) {
	std::cout << "add:" << a << "," << b << "," << c << std::endl;
	return a + b + c;
}

int multi(int a, int b, int c) {
	std::cout << "multi:" << a << "," << b << "," << c << std::endl;
	return a * b * c;
}

int main() {
	using namespace std::placeholders;

	auto f1 = std::bind(&add, _1, _2, _3);
	auto f2 = std::bind(&multi, f1, _4, _5);
	f2(1, 2, 3, 4, 5);
}