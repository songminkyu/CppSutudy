#include <iostream>

template<class T> struct eval {
	eval() { std::cout << "#1 \n"; }
};

template<template<class, class...> class TT, class T1, class... Rest>
struct eval<TT<T1, Rest...>>
{
	eval() { std::cout << "#2 \n"; }
};


template<class T1>                        struct A;
template<class T1, class T2>              struct B;
template<int N>                           struct C;
template<class T1, int N>                 struct D;
template<class T1, class T2, int N = 17>  struct E;


int main()
{
	eval < A<int>>		 eA; //#2
	eval < B<int,float>> eB; //#2
	eval < C<17>>		 eC; //#1
	eval < D<int,17>>    eD; //#1
	eval < E<int,float>> eE; //#1
}