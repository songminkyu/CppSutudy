#include <iostream>
/*

C++20에서는 람다 초기화 구문에 Pack expansion이 가능합니다
(msvc 19.22 버전에 반영됨.)

*/
template <class...Args>
auto delay_invoke_foo(Args... args)
{
	return[args...]()-> decltype(auto){
		(std::cout << ... << args) << std::endl;
	};
}

int main()
{
	delay_invoke_foo(1, 2, 3, 4)();
	return 0;
}