#include <iostream>
#include <concepts>

int main() {
	std::invocable<int, int> auto p = [](int a, int b) { return a + b; };
	std::cout << p(10, 20);
}