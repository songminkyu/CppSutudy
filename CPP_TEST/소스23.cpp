#include <iostream>

/*
C++20에 추가된 char 류 배열로의 output operator

C++ 표준에 많은 사람이 참여하면서 빠른 속도로 라이브러리가 개선되고 있다.

두 번째 스샷이 실제 구현부~. 기존 기술 몇줄로 효과적으로 개선 가능.

*/
int main()
{
	char a[4];
	std::cin >> a;
	std::cout << a;
	
}