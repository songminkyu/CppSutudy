#include <iostream>
#include <iomanip>
#include <string>
#include <cfenv>
#include <cmath>
int main() {

	std::fesetround(FE_UPWARD);
	std::cout << 1.1000 << std::endl;

	std::fesetround(FE_DOWNWARD);
	std::cout << 1.1 << std::endl;
}

