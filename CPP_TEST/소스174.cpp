#include <iostream>

/*
C++ 템플릿은 매우 공리적 공간를 기초로 한다.
무슨 말인가 하니,
예를 들어
N+1은 1+N과 같다고 흔히 생각한다.
그 흔한 생각은 실은 교환 법칙에 의존한다. 즉 모든 논리적 사고는 그보다 작은 어떤 법칙에 근간하고 또 다시 하부 법칙에 또 의존한다.
그런데 그 하부 법칙이 공집합인 상태. 더 이상 어떤 법칙이 존재하지 않는 상태. 바로 그 상태, 또는 그 공간에서 겨우 설명 가능한 C++ 템플릿 규칙이 존재한다. 실제로 그러하다.
문서를 기준으로 보면 공리 공간에는 atomic expression만 존재하나보다. 여기서 expression이 atomic하다는 것은 어떤 규칙을 적용하기 위해 expression이 변형될 수 없다는 의미. 
즉 자신만 자신의 expression를 대치할 수 있다.
*/

template<unsigned N> constexpr bool Atomic = true;
template<unsigned N> concept C = Atomic<N>;
template<unsigned N> concept Add1 = C < N + 1>;

template<unsigned N> void foo() requires Add1<1 + N == 1>
{ 
	std::cout << "#1" << std::endl; 
}

template<unsigned N> void foo() requires Add1<N + 1 == 2>
{
	std::cout << "#2" << std::endl;
}
int main()
{
	//foo<8>(); //error #1과 #2가 서로 다른 함수 -> 오버러드 레졸루션 실패.	
}