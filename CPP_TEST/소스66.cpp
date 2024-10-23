#include <iostream>

#include <vector>

#include <type_traits>

//#include <concepts>



template<class T>

struct A {

	A(T&&) { std::cout << typeid(*this).name() << std::endl; } //#1

	// class T과 함께 선언되지 않는 파라미터는 forwarding reference가 아니다.

	// 즉 위에 구문은 T에 &&과 결합해 타입을 결정할 뿐, forwarding reference가 아니다.

};



template<class T>

struct B {

	B(T&&) { std::cout << typeid(*this).name() << std::endl; } //#1과 동일.

};

template<class T> B(T&&)->B<T>; //#2 T&&는 forwarding reference



int main() {

	int i{ 10 };

	//A a1{ i }; // ERROR: A<int>가 되면 #1 이유로 인해 A(T&&)는 rvalue reference가 된다.

	A a2{ 0 };   // rvalue reference임으로 문제없음. 

	// print: struct A<int> 



	B b1{ i };  // #2에서 T는 int&로 추론한 후 생성자 호출. 따라서 B(T&&)는 B(int&)로 축약

	// print: struct B<int &> 



	B b2{ 0 };  // #2에서 T는 int로 추론한 후 생성자 호출. 따라서 B(T&&)는 B(int&&);

	// print: struct B<int> 

}