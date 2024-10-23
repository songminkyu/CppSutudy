#include <iostream>



template<int... its, typename...Ts>
void test(Ts... ts)
{
	std::initializer_list<int> datas = { ts...,its... };
	for (auto&& item : datas) std::cout << item << std::endl;
}

struct A {
	double i1, i2, i3;
	int c1, c2, c3;
};

std::ostream& operator <<(std::ostream& c, const A& a)
{
	c << a.i1 << "," << a.i2 << "," << a.i3 << std::endl;
	c << a.c1 << "," << a.c2 << "," << a.c3 << std::endl;
	return c;
}
template<int... its, typename...Ts>
void test2(Ts... ts)
{
	A datas{ ts...,its... };
	std::cout << datas;
}
int main()
{
	test<1, 2, 3>(10, 20);
	test2<1, 2, 3>(10.5, 34.5, 34.5);
}