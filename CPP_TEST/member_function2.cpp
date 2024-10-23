#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include <range/v3/range.hpp>
#include <range/v3/view.hpp>


template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	OutputIterator result,
	BinaryOperation op);


class X
{
public:
	explicit X(int value) : value(value) {}
	int getValue() const { return value; }
private:
	int value;
};


int main()
{

	auto const inputs = std::vector<X>{ X(1), X(42), X(3) };
	std::vector<int> results;

	std::transform(begin(inputs), end(inputs), back_inserter(results), std::function<int(X const&)>(&X::getValue));

	for (auto&& vectors : results)
	{
		std::cout << vectors << std::endl;
	}

	results.clear();
	

	std::cout << "# std::mem_fn 사용 했을때!" << std::endl;

	std::transform(begin(inputs), end(inputs), back_inserter(results), std::mem_fn(&X::getValue));

	for (auto&& vectors : results)
	{
		std::cout << vectors << std::endl;
	}

	//std::cout << "# range 라이브러리를 통해 맴버 펑션 호출" << std::endl;

	//auto results = inputs | ranges::view::transform(&X::getValue); // 컴파일이 왜 안되지...?


}