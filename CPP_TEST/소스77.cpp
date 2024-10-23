#include <iostream>
#include <string>


/*
스펙 문서를 읽다가 incomplete type이 가장 훌룡하게 사용되는 영역이 
template argument 영역이라는 사실을 새삼 느끼는~.

최종 사용되는 시점(인스턴스가 요구되는 시점)에서는 complete type으로 
수렴하는 느낌도 멋지고.

C++20의 smart pointer는 incomplete type를 더욱 적극 활용하고~

*/
template<class T>
struct A {
	static T datas[]; // T[]는 불완전 타입.
};

template<class T>
T A<T>::datas[1] = {};

template<>
int A<int>::datas[2] = { 1,2 };

template<>
double A<double>::datas[3] = { 1.1, 2.2, 3.3 };

template<>
std::string A<std::string>::datas[4] = { "test1","test2", "test3", "test4" };

int main() {
	for (auto&& item : A<int>::datas) std::cout << item << ' '; std::cout << '\n';
	for (auto&& item : A<double>::datas) std::cout << item << ' '; std::cout << '\n';
	for (auto&& item : A<std::string>::datas) std::cout << item << ' '; std::cout << '\n';
}