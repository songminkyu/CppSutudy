#include <iostream>

template<class T>					class A {/*.....*/ };
template<class T, class U = T>		class B {/*.....*/ };
template<class ... Types>			class C {/*.....*/ };

template<template<class> class P>	class X{/*....*/ };

/*
C++17부터 달라진 template 아규먼트의 최소 매칭을 허용한다. 생각보다 해당 규약이 파급력이 세다~
*/

int main()
{

	[[maybe_unused]] X<A> xa;
	[[maybe_unused]] X<B> xb;
	[[maybe_unused]] X<C> xc;
}