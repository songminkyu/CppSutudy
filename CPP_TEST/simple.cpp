#include <iostream>
#include <tuple>
#include <utility>
#include <Ranges_v3/range/v3/all.hpp>

using namespace ranges;

using Tuple = std::tuple<int, char, bool>;

template <typename T>
void _type(const T&) {

#ifdef __linux__ 	
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#elif _WIN32	
	std::cout << __FUNCSIG__ << std::endl;
#else
#endif

}

std::ostream& operator<<(std::ostream& out, const Tuple& t) {
	const auto& first = std::get<0>(t);
	const auto& second = std::get<1>(t);
	const auto& third = std::get<2>(t);
	out << "(" << first << ", " << second << ", " << third << ")";
	return out;
}

int main() {
	std::vector<Tuple> db = {
		{1, 'a', true},  {2, 'd', true},  {3, 'g', false},
		{4, 'b', false}, {5, 'e', true},  {6, 'h', false},
		{7, 'c', true},  {8, 'f', false}, {9, 'i', true},
	};

	// select
	auto is_even = [](const auto& t) { return std::get<0>(t) % 2 == 0; };
	auto is_odd = [](const auto& t) { return std::get<0>(t) % 2 == 1; };
	auto evens = db | views::filter(is_even);
	auto odds = db | views::filter(is_odd);

	for_each(evens, [](const auto& t) { std::cout << t << std::endl; });
	for_each(evens, [](const auto& t) { std::cout << t << std::endl; });

	// project
	auto first = [](const auto& t) { return std::get<0>(t); };
	auto second = [](const auto& t) { return std::get<1>(t); };
	auto third = [](const auto& t) { return std::get<2>(t); };
	auto ints = db | views::transform(first);
	auto chars = db | views::transform(second);
	auto bools = db | views::transform(third);

	std::cout << ints << std::endl;
	std::cout << chars << std::endl;
	std::cout << bools << std::endl;

	// zip
	auto zipped = views::zip(db, db);
	for_each(zipped, [](const auto& t) {
		_type(t);
		const auto& first = std::get<0>(t);
		const auto& second = std::get<1>(t);
		std::cout << "(" << first << ", " << second << ")" << std::endl;
		});

	// types
	std::cout << std::endl;
	std::cout << "evens:" << std::endl;
	_type(evens);
	std::cout << "odds:" << std::endl;
	_type(odds);
	std::cout << "ints:" << std::endl;
	_type(ints);
	std::cout << "chars:" << std::endl;
	_type(chars);
	std::cout << "bools:" << std::endl;
	_type(bools);
	std::cout << "zipped:" << std::endl;
	_type(zipped);
}