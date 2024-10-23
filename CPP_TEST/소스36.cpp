#include <iostream>
#include <string>

template<typename R, typename... Args>
using FN_PTR = R(*)(Args...);

struct A {
	template<typename R, typename... Args>
	operator FN_PTR<R, Args...>() {
		return [](Args... args)->R {
			return(... + args);
		};
	}

};

int main()
{
	A a{};
	FN_PTR<int, int, int> fn1 = a;
	std::cout << fn1(100, 200) << std::endl;

	FN_PTR<std::string, std::string, const char*>  fn2 = a;
	std::cout << fn2("song", "minkyu");

}