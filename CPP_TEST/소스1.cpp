#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
/*

max_element과 minmax_element는 element를 선택하는 과정이 
스펙 문서상으로 미묘하게 다르다. 그래서 확인들어갑니다~

*/

struct A
{
	int i, j;
	A(int _i, int _j) : i(_i), j(_j)
	{

	}

	bool operator<(const A& rhs) const { return i > rhs.i; }
	

	template <typename T> friend T& operator<<(T& out, const A& a) {
		out << "(" << a.i << ", " << a.j << ")";

		return out;
	}
};


struct B
{
	int i, j;
	B(int _i, int _j) : i(_i), j(_j)
	{

	}

	bool operator<(const B& rhs) const { return i < rhs.i; }


	template <typename T> friend T& operator<<(T& out, const B& a) {
		out << "(" << a.i << ", " << a.j << ")";

		return out;
	}
};

int main()
{
	std::vector<A> datasA = {
		{1,5},{2,4},{3,3},{4,2},{4,1}
	};

	
	auto maxIterA = std::max_element(datasA.begin(), datasA.end());
	std::cout << "std::max_element : " << *maxIterA << std::endl;

	auto minmaxIterA = std::minmax_element(datasA.begin(), datasA.end());
	std::cout << "std::minmax_element : " << *minmaxIterA.first <<"," << *minmaxIterA.second << std::endl;

	std::vector<B> datasB = {
		{1,5},{2,4},{3,3},{4,2},{4,1}
	};

	auto minmaxIterB = std::minmax_element(datasB.begin(), datasB.end());
	std::cout << "std::minmax_element : " << *minmaxIterB.first << "," << *minmaxIterB.second << std::endl;

	const auto v = { 3, 9, 1, 4, 2, 5, 9 };
	const auto [min, max] = std::minmax_element(begin(v), end(v));

	std::cout << "min = " << *min << ", max = " << *max << '\n';

}