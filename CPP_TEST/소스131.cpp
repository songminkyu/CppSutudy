#include <iostream>

enum struct COLOR {
	RED,
	GREEN
};

int main()
{
	int n{ 10 };
	switch (n)
	{
		std::cout << "may never called \n";//해당 구문은 실행되지 않음

	case 10:
		std::cout << n << std::endl;
		[[__fallthrough]];
	default:
		std::cout << "default \n";
	}
	//아래 구문이 안되는건 C++20 완벽하게 업데이트 안되엇기때문.... 추후 될듯.

	//COLOR color{ COLOR::RED };
	//switch (color)
	//{
	//using enum COLOR;
	//case RED: std::cout << "RED" << std::endl; break;
	//case GREEN: std::cout << "RED" << std::endl; break;
	//default:
	//	std::cout << "default \n";
	//	break;
	//}

}