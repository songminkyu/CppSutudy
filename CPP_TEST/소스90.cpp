#include <iostream>

void test(bool v)
{
	int a[] = { 1,2,3,4 };
	int b[] = { 1,2,3,4,5,6,7,8 };

	std::cout << sizeof(v ? a : b) << std::endl;
}

void test1()
{
	bool v = false;
	int b[] = { 1,2,3,4,5,6,7,8 };
	std::cout << sizeof(v ? throw "" : b) << std::endl;
}

int main()
{
	test(true);
	test(false);

	test1();

	return 0;

}