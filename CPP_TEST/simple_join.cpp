#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>
#include <Ranges_v3/range/v3/all.hpp>

using namespace ranges;

using intint = std::tuple<int, std::string>;

int key(const intint& xy) { return std::get<0>(xy); }

template <typename L, typename R>
std::ostream& operator<<(std::ostream& out, const std::tuple<L, R>& xy) {
	const L& x = std::get<0>(xy);
	const R& y = std::get<1>(xy);
	out << "(" << x << ", " << y << ")";
	return out;
}

template <typename Rng1, typename Rng2>
auto join(const Rng1& xs, const Rng2& ys) {
	return xs  //
		| views::for_each([&ys](const auto& x) {
		auto joined =  //
			ys         //
			| views::filter(
				[&x](const auto& y) { return key(y) == key(x); })  //
			| views::transform(
				[&x](const auto& y) { return std::make_tuple(x, y); });
		return yield_from(joined);
			});
}

int main() {
	/*std::vector<intint> xs = { {0, 1}, {1, 2}, {2, 3}, {2, 4}, {3, 5} };
	std::vector<intint> ys = { {1, 10}, {2, 20}, {3, 30},
							  {3, 40}, {5, 50}, {6, 60} };*/

	std::vector<intint> xs = { {0, "song"}, {1, "park"},{2, "char"} };
	std::vector<intint> ys = { {1, "min"}, {0, "kong"}, {2, "int"} };

	for_each(join(xs, ys), [](const auto& t) { std::cout << t << std::endl; });
}