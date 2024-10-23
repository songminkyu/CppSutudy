#include <concepts>
#include <iostream>
#include <string>


/*
std::convertible_to for conversions with fewer surprises std::convertible_to helps you to express that you only accept 
types that are convertible to another type - a type that you specify. The conversion can be both explicit or implicit. For example, 
you can say that you only accept types that can be converted into a bool. As the first parameter, 
you pass the type you want a conversion to be valid From and as the second, the type you want to be able to convert To, 
in our case, bool.

*/
template <typename T>
void fun(T bar) requires std::convertible_to<T, bool> {
	std::cout << std::boolalpha << static_cast<bool>(bar) << '\n';
}

int main() {
	fun(5); // OK an int can be converted into a pointer
   //  fun(std::string("Not OK")); // oid fun(T) requires  convertible_to<T, bool> [with T = std::__cxx11::basic_string<char>]' with unsatisfied constraints
}