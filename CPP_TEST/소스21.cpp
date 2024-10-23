#include <iostream>

int main()
{
	int i2 = 42;
	int&& rri = static_cast<int&&>(i2);
	// bound directly to i2

	rri = 100;
	
	std::cout << i2 << std::endl;

}