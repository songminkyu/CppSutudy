#include <iostream>


/*
C++20에서는 generic lambdas 구문에 template-parameter-list이 
가능합니다(msvc 19.22버전에 반영됨).

*/
int main()
{
	auto f = []<typename ...T>(int z, T&& ...args) {
		std::cout << z << std::endl;
		(std::cout << ... << std::forward<T>(args)) << std::endl;
	};

	f(1, 2, 3);

	return 0;
}