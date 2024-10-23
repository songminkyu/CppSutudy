#include <iostream>
#include <algorithm>
#include <type_traits>
//#include <concepts>

template<class T, auto N>
struct A {
	T datas[N] = {};
	A(T(&mdatas)[N]) { std::copy_n(mdatas, N, datas); }
	A(T(&& mdatas)[N]) { std::copy_n(mdatas, N, datas); }
	T* begin() { return datas; }
	T* end() { return datas + N; }
};

//template<class T, auto N> A(T(&)[N])->A<T, N>;
int main() {
	A a({ 1,2,3,4 });
	for (auto& item : a) item *= 10;
	for (auto& item : a) std::cout << item++ << ' ';
	std::cout << std::endl;

	double fa[] = { 1.12, 1.23 };
	A a1(fa);
	for (auto& item : a1) item *= 12.4;
	for (auto& item : a1) std::cout << item++ << ' ';
	std::cout << std::endl;

}