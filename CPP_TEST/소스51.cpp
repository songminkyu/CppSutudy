#include <iostream>
#include <type_traits>
#include <concepts>

template<typename T> requires (sizeof(T) != sizeof(int))
using Ptr = T*;

int main()
{
	Ptr<char> a1 = nullptr;
	Ptr<short> a2 = nullptr;
	Ptr<double> a3 = nullptr;
	//Ptr<int> a4 = nullptr; //ERROR
}