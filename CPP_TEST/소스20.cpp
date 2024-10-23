#include <iostream>

struct A
{
	int age;
	int level;
};

int main()
{
	A a{ .age{10}, .level{200} };

	std::cout << a.age << std::endl;
	std::cout << a.level << std::endl;
}