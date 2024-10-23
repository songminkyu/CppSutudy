#include <iostream>
#include <type_traits>

template<typename T> concept is_true_value = T::value;

template<is_true_value>
struct A
{

};

struct MyStruct1
{
	static inline constexpr bool value = true;
};

struct MyStruct2
{

};

int main() {
	A < MyStruct1> a{};
	//A<MyStruct2> a{}; Error
}