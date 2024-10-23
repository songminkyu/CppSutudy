
#include <iostream>
#include <string>

int divide(int a, int b, int c, std::string asdasd)
{

	std::cout << asdasd.c_str() << std::endl;
	return a * b / c;
}
int add(int a, int b)
{
	return a + b;
}

template<typename RT,typename ...Args>
RT Callfp(auto(&Fn)(Args...)->RT, Args... args)
{	
	return Fn(args...);
}

int main()
{	
	std::string str= "asdasd";
	std::cout << Callfp(add, 10, 20) << std::endl;
	std::cout << Callfp(divide, 10, 20, 30, str) << std::endl;
}