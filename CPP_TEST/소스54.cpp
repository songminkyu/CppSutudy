#include <iostream>

/*
lambda capture 구문에 pack과 pack expansion 적용해보기
*/
template<typename ...Ts>
void test(Ts... ts)
{
	[...args = ts] (){
		(std::cout << ... << args);
		
	}();
}
template<typename ...Ts>
void test2(Ts... ts)
{
	[ts...] (){
		(std::cout << ... << ts);

	}();
}

int main()
{
	test("hello","\n", 12, "\n", 10.5,"\n");
	test2("hello", "\n", 12, "\n", 10.5);
}