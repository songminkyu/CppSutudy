#include <utility>
#include <tuple>
#include <iostream>

struct A {
	A(int,int){


		std::cout << "arg1에 의해 호출 됨" << std::endl;
	}
};

struct B {
	B(double,double,double){
		std::cout << "arg2에 의해 호출 됨" << std::endl;
	}
};

int main()
{
	std::tuple arg1{ 1, 2 };
	std::tuple arg2{ 1.1, 2.3, 5.6 };

	std::pair<A, B> ab(std::piecewise_construct, arg1, arg2);


}