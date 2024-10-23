#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>


/*

binary_function, std::not2... 군 함수들은 모두 lambda나 std::bind로 더 효과적으로 사용될 수 있다. 
이러한 이유로 C++17에는 모두 deprecated되었고 C++20에는 removed된 상태다.

이러한 이유로 이전 버전에서 C++20로 업그레이드하면 쉽게 만나는 열에 일곱 컴파일 
오류가 이들 함수를 찾을 수 없다는 내용이다. 
차분히 아래 스샷처럼 적절히 std::bind나 lambda로 풀어주면 된다.

              C++17부터 이놈 삭제됨(std::binary_function) 
                            ▼
struct same : std::binary_function<int,int,bool>
{
   do something....
}
                                                       C++17부터 이놈 삭제됨(std::not2) 
																  ▼
std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), std::not2(same()));

*/
struct same
{
	bool operator()(int a, int b) const { return a == b; }
};

int main()
{
	std::vector<int> v1{ 0,1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> v2{ 10,9,8,7,6,5,4,3,2,1,0 };
	std::vector<bool> v3( v1.size() );

	std::transform(v1.begin(), v1.end(), v2.begin(), v3.begin(),
		[](auto&& a, auto&& b) {return !same{}(a, b); }
	);

	std::cout << std::boolalpha;

	for (std::size_t i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i] << ' ' << v2[i] << ' ' << v3[i] << '\n';
	}
}