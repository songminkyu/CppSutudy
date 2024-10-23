#include <iostream>
#include <string>
#include <concepts>

template<typename T, typename U>
concept CS = sizeof(T) > sizeof(U);

template <CS<char>...Ts>
struct S5 {

};

/*
CS<char>...Ts는
 ( CS<Ts,char>&&...) 로 folding 된다.
 따라서 char 보다 큰 사이즈를 가진 
 type-parameter만 받을 수 있다.
*/

int main() {
	S5<int, double, short> a; // ok
	S5<char,int> b;          //error
}