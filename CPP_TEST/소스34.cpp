#include <iostream>

int main()
{
	alignas(128) char buffer[10];
	std::cout << (reinterpret_cast<int>(&buffer[0]) % 128);
	//buffer의 메모리 주소를 128 배수 위치에서 시작하기



		
}