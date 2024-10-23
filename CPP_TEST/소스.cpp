#include <iostream>
#include <complex>

int main()
{
	std::complex<int> z(1, 10);

	int(&v)[2] = reinterpret_cast<int(&)[2]>(z);
	std::cout << v[0] << ", " << v[1] << std::endl;

	std::cout << z << std::endl;
}