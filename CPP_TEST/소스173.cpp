#include <iostream>
#include <concepts>

template<typename T> concept C = sizeof(T) > 2;
template<typename T> concept D = C<T> && sizeof(T) > 4;

template<typename T> struct S {
	S() requires C<T> {std::cout << "#1 \n"; }
	S() requires D<T> {std::cout << "#2 \n"; }
};

void main()
{
	//S<char> s1; //error :  no matching contrcutor
	S<char[3]> s2{};
	S<char[8]> s3{};
}