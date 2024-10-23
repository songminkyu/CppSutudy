#include <bitset>
#include <sstream>
#include <iostream>
int main()
{
	std::bitset<8> b1{ "**!!*!", std::string::npos, char('*'), char('!') };
	std::cout << b1.to_string(char('*'), char('!')) << std::endl;

}