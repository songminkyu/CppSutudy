#include <iostream>

//https://godbolt.org/
/*
C++20���� ���ø�(P)�� ���ø� �Ķ���ͷ� ����� �� ���Ǵ�
���ø� �ƱԸ�Ʈ(A) ������ C++20���� ���� �� ����.
����??�ϰ� ����� ����ϸ�
P is at least as specialized as A.
���Ҹ�?? A�� ���� ���� �߿� P�� ����ϴ� ���¸� ���� �� �ִٸ� ����Ѵ�.
MSVC/GCC���� ������ ����.

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
