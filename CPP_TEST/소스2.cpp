#include <iostream>
#include <algorithm>
#include <set>
#include <iterator>

int main()
{
	std::multiset<int> v1{ 1,1,3,4,5 };
	std::multiset<int> v2{ 1,1,1,6,7 };

	//합집합 구하기
	std::set_union(
		v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		std::ostream_iterator<int>(std::cout, " ")
	);
	std::cout << std::endl;

	//교집합 구하기.
	std::set_intersection(
		v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		std::ostream_iterator<int>(std::cout, " ")
	);
	std::cout << std::endl;

	//차집합 구하기.
	std::set_difference(
		v1.begin(), v1.end(),
		v2.begin(), v2.end(),
		std::ostream_iterator<int>(std::cout, " ")
	);
	std::cout << std::endl;

}