#include <iostream>

//https://godbolt.org/
/*
C++20부터 템플릿(P)을 템플릿 파라미터로 사용할 때 허용되는
템플릿 아규먼트(A) 조건이 C++20부터 조금 더 유연.
간단??하게 영어로 언급하면
P is at least as specialized as A.
뭔소리?? A의 여러 형태 중에 P가 허용하는 형태를 만들 수 있다면 허용한다.
MSVC/GCC까지 구현된 상태.

*/

template<class T>				class A { void print() { std::cout << "#A" << "\n"; } };
template<class T, class U = T>	class B { void print() { std::cout << "#B" << "\n"; } };
template<class... Types>		class C { void print() { std::cout << "#C" << "\n"; } };

template<template<class ...> class Q> class Y { /* ... */ };


template<auto n>                      class D { /* ... */ };
template<template<int> class R>       class Z { /* ... */ };


int main() 
{
    [[maybe_unused]] Y<A> ya;    // OK
    [[maybe_unused]] Y<B> yb;    // OK
    [[maybe_unused]] Y<C> yc;    // OK

    [[maybe_unused]] Z<D> zd;    // OK
}
