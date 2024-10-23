#include <iostream>
#include <string>
#include <tuple>
#include <pipes/pipes.hpp>
struct A {
	int         idx;
	std::string name;
};

int main() {

	A a{1,"song"};
	auto [idx, name] = a;
	auto f = [idx, name] { return std::tuple<int,std::string>(idx, name); };
	
	std::string s;
	int i;
	std::tie(i, s) = f();
	

	std::cout << i << std::endl;
	std::cout << s << std::endl;
	std::cout << std::get<0>(f()) << std::endl;
	std::cout << std::get<1>(f()) << std::endl;
	//std::cout << f() << std::endl;

}