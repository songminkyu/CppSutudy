#include <iostream>

void test1() { std::cout << "test 1" << std::endl;}
void test2() { std::cout << "test 2" << std::endl; }
void test3() { std::cout << "test 3" << std::endl; }

int main()
{
	void(*gs[])() = {
		test1,test2,test3,
	};
	for (auto& p : gs) p();

}