#include <iostream>
#include <type_traits>
#include <functional>

struct B { 

	int f() 
	{
		std::cout << "hellow world" << std::endl;
		return 0;
	} 

};

struct L: B{};
struct R : B {};
struct D : L,R {};

int main()
{

	B b;
	L l;
	R r;
	D d;


	int(B:: * pb)() = &B::f;
	//pb로부터 변형된 멤버 포인터를 선언한다.

	int(L:: * pl)() = pb;
	int(R:: * pr)() = pb;

	int(D:: * pdl)() = pl;
	int(D:: * pdr)() = pr;

	std::cout << std::boolalpha;
	
	//맴버 포인터 비교 연산이 true인경우
	//(pd로 직접 할당 받은 pl과 pr는 pb와 같다.)	
	std::cout << (pl == pb) << "," << (pr == pb) << std::endl;

	//맴버 포인터 비교 연산이 true인경우
	//(pd로부터 간접(pl 또는 pr를 경유한) 할당 받은 pdl과 pdr은 서로 다르다.)
	std::cout << (pdl == pdr) << std::endl;

	auto _pb = (b.*pb)();

	auto _pl = (l.*pb)();
	auto _pr = (r.*pb)();

	auto _pdl = (d.*pl)();
	auto _pdr = (d.*pr)();
	
	return 0;


}