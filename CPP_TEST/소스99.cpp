#include <iostream>

// variable template를 explicit specialization 해보기

using FN = void(*)(int);

template<typename T>  T var = {};
template<> FN var<FN[3]>[3] {
	[](int) {std::cout << "#1" << std::endl; },
	[](int) {std::cout << "#2" << std::endl; },
	[](int) {std::cout << "#3" << std::endl; }
};

int main()
{
	for (auto&& item : var<FN[3]>)
	{
		item(10);
	}
}
