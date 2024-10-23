#include <iostream>

struct A
{
protected:
	struct ProtectedA {};
	void test();
};

template<typename T1, typename T2> struct X{ };

template<typename T1> struct X<T1, A::ProtectedA> : A {
	A::ProtectedA val = { }; //하지만 실제 사용되는 위치에서는 access 체크 한다, A로부터 상속 받는다.
};
// template class specialization 의 argument list는 access를 체크 하지 않는다.

void A::test() {
	X<int, A::ProtectedA> datas{  };
}

int main()
{
	X<int, A::ProtectedA> datas{};
	//하지만 실제 사용 되는 위치에서는 access 체크한다. Error!!!

	
}