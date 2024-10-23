#include <iostream>

//https://godbolt.org/

template<class T> struct eval {
	void print() { std::cout << "#1" << "\n"; }
};

template<template<class, class...> class TT, class T1, class...Rest>
struct eval<TT<T1, Rest...>>
{
	void print() { std::cout << "#2" << "\n"; }
};

template<class T1> struct A;
template<class T1, class T2> struct B;
int main()
{
	eval<A<int>> eA;
	eval<B<int, float>> eB;

	eA.print(); //#2
	eB.print();  //#2
}