#include <vector>
#include <initializer_list>
#include <iostream>

/*
C++17부터 지원하기 시작한
class template deduction guide는 좋은 트릭 재료!!
일반적으로 클래스 템플릿 아규먼트는 추론할 수 없습니다.
왜냐하면 아규먼트 추론이 함수에서 사용되는 overload resolution 
과정에서 진행되는데 클래스는 함수가 아니니까요.
하지만 표준에서는 class template deduction guide라는 함수꼴 문법 가이드를 
도입해서 클래스에서 직접 추론하지는 않지만 함수꼴 문법에서 overload resolution를 
사용해 추론하도록 가이드해 주고, 추론된 결과를 클래스 템플릿 추론 결과로 사용하는 구조입니다.
*/
template <class T, class U, class V>
struct Foo {
	T bar;
	std::vector<U> baz;
	V foobar;
};
template <class T, class U, class V>
Foo(T, std::initializer_list<U>, V)->Foo<T, U, V>;
int main() {
	auto test = Foo{ 42, {3.14, 2.718, 1.618}, 'x' };


	std::cout << test.bar << std::endl;	
	std::cout << test.foobar << std::endl;

}