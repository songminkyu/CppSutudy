#include <iostream>


/*

이것이 가능한 거였군. 이런 코딩을 어떻게 생각하는지.. ㅋㅋ
 세부 스펙 내용을 3개 정도 정확하게 알고 있을 때나 가능한 코딩...
TYPE:action 형태로 특정 타입과 action를 컴파일 시간에 맵핑해주는 기능.

어셈블러 코딩은 13줄.. std::cout로 바꾸더라도 25줄..


컴파일 시간에는 존재하고 컴파일 시간에 사용한다면 가능~ 
어셈블러 코딩을 보면 계산 결과가 어셈에 못처럼 박혀있는 
구조(최적화가 친화적인 구조).

그러고보면 컴파일 시간의 deterministic function composition이 가까운 시일내에 가능할지도~
*/

class tag;

template<class>
struct type { friend constexpr auto get(type); };

template< class TKey, class TValue>
struct set { friend constexpr auto get(TKey) { return TValue{}; } };

void foo() {
	if constexpr(false)
		if (false) {
			constexpr auto call = [](auto value) {std::cout << "called " << value; };
			void(set<type<tag>, decltype(call)>{ });
		}
}

int main()
{
	get(type<tag>{})(42);
}