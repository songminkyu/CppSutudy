#include "fmt/chrono.h"
#include <iostream>
int main()
{
	using namespace std::literals::chrono_literals;

	std::string s;
	s = fmt::format("Default format: {} {} \n", 42s, 100ms);
	std::cout << s << std::endl;
	
	s = fmt::format("strftime-like format:{:%H:%M:%S}\n", 3h + 15min + 30s);
	std::cout << s << std::endl;
	

}