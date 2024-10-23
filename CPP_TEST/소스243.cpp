/*
아래 설명을 먼저 읽어주시면 좋아요~
constraint는 이항 논리 연산자 conjunction과 disjunction이 존재한다.
두 표현식을 비교 연산할 때 연산자를 기준으로  정규화된 표현식으로 변경
한 후, 두 표현식이 모두 포함한 subexpression를 모두 제거하고 상태에서
한쪽은 empty인데, 다른 한쪽이 남아있으면 남은 쪽이 더 특화된 expression
으로 정의할 수 있게 된다.즉 연산자를 정의하면 서로 다른 두 표현식을 비교
할 수 있다는 것이  핵심이다.흥미로운 내용은 논리 부정 연산자 !가 constraint 
연산자가 아닌 atomic constraint중 하나로 언급하고 있다는 것이다. 이 부분을
어찌 설명할까 고민이긴 한데, 같은 람다 함수라도 다른 문맥에 존재하면 서로 다른
람다 함수로 분류되듯, atomic constraint도 그러하다. 같은 표현식이라도 다른 
문맥상에 존재하면, 같은 표현식이 아니다. 즉, 비교 불가한 두 대상일 뿐이다.
역으로 같은 문맥의 atomic constraint에서 발원하면 동일한 표현식으로 판단한다.
또한 atomic constraint는 문맥 자체가 온전히 해석되어야 하고, 해석 과정에서 
문제가 발생하면 requirement 불만족이 아니라 문법 오류로 분리된다.
그러면 이러한 원리를 기초로 아래 예제를 보자.
*/
#include <iostream>

template<class T> concept sad = false;

template<class T> void f1(T) requires(!sad<T>) { std::cout << "#1\n"; }
template<class T> void f1(T) requires(!sad<T>) && true { std::cout << "#2\n"; }

template<class T> concept not_sad = !sad<T>;
template<class T> void f2(T) requires not_sad<T>{std::cout << "#3" << "\n"; }
template<class T> void f2(T) requires not_sad<T> && true 
{std::cout << "#4" << "\n"; }

template <class T> concept sad_nested_type = sad<typename T::type>;
template <class T> void f3(T) requires (!sad<typename T::type>) {std::cout << "#5\n";}
template <class T> void f4(T) requires (!sad_nested_type<T>) {
	std::cout << "#2\n";
}

int main()
{
	// f1(42); Error ambiguous
	f2(42); //#4
	// f3(42); // 구문 오류
	f4(42); //#2
}