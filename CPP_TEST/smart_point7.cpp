#include <iostream>
#include <memory>

/*
스펙 문서에 empty shared_ptr 관련 내용이 있어 만들어 본 예제.

empty shared_ptr는
ownership는 없지만
저장된 포인터는 있는 shared_ptr이다.
(ownership과 저장하는 포인터를 서로 다르게 갖는 것이 때론 매우 유용할 수 있다. 실전 코딩에서)

std::cout으로 주소를 출력해 관리하는 포인터를 확인할 수 있다. 하지만 ownership는 없으니 소멸자가 호출되지 않는다.

13번줄 코딩이 핵심이라고 할 수 있는데 첫인자는 ownership를 share할 대상이고, 두번째 인자는 저장할 포인터다. 
이때 첫인자로 empty shared_ptr를 넣어주면 만들어 낼 수 있다.

*/

struct A {
	~A() { std::cout << "~A" << std::endl; }
};

int main()
{
	A* a = new A();
	{
		std::shared_ptr<A> nullA1{};
		std::shared_ptr<A> nullA2{ nullA1,a };
		std::cout << nullA2 << std::endl;
	}
	delete a;
}