#include <iostream>
#include <bitset>
#include <sstream>

int main()
{
	std::string bit_string = "00110101";
	std::istringstream ss(bit_string);
	std::bitset<8> b1;
	ss >> b1;
	std::cout << b1 << std::endl;
}