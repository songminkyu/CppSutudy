#include <iostream>

int i = 100;
struct A {
private : 
	inline static int i = 500;
public:
	void test(int p = i) { // i의 접근 권한은 ? test의 접근 권한과 같다.
		std::cout << p << std::endl;
	}

};

int main()
{
	A a;
	a.test();
}