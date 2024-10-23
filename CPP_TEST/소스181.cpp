#include <iostream>
#include <variant>

#define ST struct

ST A{
	A(int, float) { std::cout << "called" << std::endl; };
	A(std::string, float) { std::cout << "song called" << std::endl; };
};


int main()
{
	std::variant<int, float, A> dat{ std::in_place_type_t<A>{},1, 3.5f };
	std::variant<std::string, float, A> dat2{ std::in_place_type_t<A>{},"song", 3.5f };

}