#include <iostream>

/*
variable template으로 배열 사용해보기
*/

template<typename T> T var = { };


int main()
{

	int i = 0;
	for (auto&& item : var<int[16]>) {
		item = i++;
	}

	for (auto&& item : var<int[16]>)
	{
		std::cout << item << " ";
	}
}
