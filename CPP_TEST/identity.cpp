#include <iostream>
#include <functional>

void test(int, int) { std::cout << "#1" << std::endl; }

int main()
{
	int z{ 10 };
	std::identity f;
	f(test)(10, 20);
	f(z) = 100;

	std::cout << z << std::endl;
	
}