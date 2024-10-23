#include <iostream>
#include <string>

template<int...args>
void test()
{
	( (std::cout << std::string(20, '-') << '\n') << ... << args ) << '\n' << std::string(20, '*');
}

int main()
{
	
	test<1, 2, 4, 8>();
}