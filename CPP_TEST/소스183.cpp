/*
 https://godbolt.org/z/bzcsar
표준 라이브러리에서
튜플을 apply로 전달해 처리하는 패턴이 자주 등장하는군.
아마도 전달된 아규먼트를 튜플로 쉽게 바꿀 수 있고, 타입 추적이 쉽다보니, 
라이브러리가 사용하는 특수한 타입을 중간에 주입하기도 편하기 때문일듯!!
튜플은 C++ 프로그래머에게 보석과 같은 타입인듯!!
튜플을 얼마나 자유자재로 가지고 놀 수 있느냐가 C++ 제어 능력의 일부로 평가 되어야 할듯. 
표준에 사용된 예를 보면 타입을 묶었다, 풀었다, 삽입했다.. 마치 트랜스포머를 보는 듯.
*/

#include <iostream>
#include <tuple>
#include <memory>
struct A {
	A(std::string, int) { std::cout << "called \n"; }
};

int main()
{
	std::tuple<std::string, int> dat{ "test",1 };

	std::apply([]<class...U>(U&&...xs) {
		A{ std::forward<U>(xs)... };
	}, dat);
}