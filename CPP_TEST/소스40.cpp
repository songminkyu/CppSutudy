#include <iostream>

template <char ... chars>
std::string operator "" _x()
{
	std::string val;
	val.reserve(sizeof...(chars));
	(val += ... += chars);
	return val;
}

int main()
{
	std::cout << 1'024.67_x;
}