#include <iostream>
#include <string>
#include <type_traits>
template<typename T> concept C = requires (T t) { t.f(); };
template<typename T> concept D = C<T> && requires (T t) { t.g(); };

template<template<C> class P> struct S { };
// concept를 사용하는 template 파라미터

template<C> struct X { };
template<D> struct Y { };
template<typename T> struct Z { };

int main() {
	[[maybe_unused]] S<X> s1;	// template 아규먼트과 equivalent constraints 매칭	(C⊆X)
	//[[maybe_unused]] S<Y> s2; // Y 아규먼트과 최소 매칭이 아님(C⊈Y)
	[[maybe_unused]] S<Z> s3;	// Z 아규먼트과 최소 매칭      (C⊆Z)
	// template 아규먼트과 최소 매칭이란?
	//     아규먼트의 요소 ∃x가 파라미터로 사용될 수 있다.
	// 다르게 표현하면
	//     template 아규먼트가 primary이고 template 파라미터가 specialization이다.
}