#include <bitset>
#include <sstream>
#include <iostream>

int main()
{
	// ! = 1  
	// * = 0 
	std::bitset<8> b1{ "**!!*!*!", std::string::npos, char('*'), char('!') };
	std::cout << b1 << std::endl;
}