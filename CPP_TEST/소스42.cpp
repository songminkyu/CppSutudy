#include <iostream>
#include <concepts>


/*
이렇게 하면 간단히 bounded type-template parameter가 가능해진다.

이렇게 템플릿 파라미터에서 type-contraint으로 immediately-declared constraint를 사용한다고 한다.

여기서 눈여겨봐야할 부분이 한가지 더 있는데, concept 선언에서 ...Us가 있고, 템플릿에 사용될 때 ... 
Ts가 또 있는데, 두 ... 구문이 어떻게 형태로 합성되는지 관심을 가져야 한다. 아직 표준 제안자의 상상력을 자극하는 파트 중에 하나가 ... 
구문간 연산을 어떻게 정의할까?라고 할 수 있다. 마치 두 벡터간의 곱으로 정의할거냐, 합으로 정의할 꺼냐.. 아니면 두 차원간으로 만들어진 Cartesian coordinate system이냐..
*/
template<typename T, typename ...Us>
concept AcceptTypes = (std::is_same_v<Us, T> || ...);


struct AcceptType1 {};
struct AcceptType2 {};

template <AcceptTypes< AcceptType1, AcceptType2>>
struct S5{};

int main() {
	[[maybe_unsued]] S5< AcceptType1 > a; //ok
	[[maybe_unsued]] S5< AcceptType2 > b; //ok
	//S5<int >error1;					 //error
}
