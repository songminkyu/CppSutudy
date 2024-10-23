#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>
#include <Ranges_v3/range/v3/all.hpp>

using namespace ranges;

using intint = std::tuple<int, int>;

int key(const intint& xy) { return std::get<0>(xy); }

template <typename L, typename R>
std::ostream& operator<<(std::ostream& out, const std::tuple<L, R>& xy) {
	const L& x = std::get<0>(xy);
	const R& y = std::get<1>(xy);
	out << "(" << x << ", " << y << ")";
	return out;
}

template <typename T>
void type(const T&) {
#ifdef __linux__ 	
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#elif _WIN32	
	std::cout << __FUNCSIG__ << std::endl;	
#else
#endif
}

class Join {
public:
	auto operator()(const common_pair<intint, intint>& xy) {
		return yield_from(views::all(newly_joined(xy)));
	}

private:
	const std::vector<std::tuple<intint, intint>>& newly_joined(
		const common_pair<intint, intint>& xy) {
		const intint& x = std::get<0>(xy);
		const intint& y = std::get<1>(xy);

		newly_joined_.clear();
		if (key(x) != -1) {
			left_[key(x)].push_back(x);
			for (const intint& y : right_[key(x)]) {
				newly_joined_.push_back({ x, y });
			}
		}
		if (key(y) != -1) {
			right_[key(y)].push_back(y);
			for (const intint& x : left_[key(y)]) {
				newly_joined_.push_back({ x, y });
			}
		}

		return newly_joined_;
	}

	std::map<int, std::vector<intint>> left_;
	std::map<int, std::vector<intint>> right_;
	std::vector<std::tuple<intint, intint>> newly_joined_;
};

template <typename Rng1, typename Rng2>
auto join(const Rng1& xs, const Rng2& ys) {
	auto negative_ones = views::generate([]() { return intint{ -1, -1 }; });
	return views::zip(views::concat(xs, negative_ones),
		views::concat(ys, negative_ones))  //
		| views::take_while([](const auto& xy) {
		auto x = std::get<0>(xy);
		auto y = std::get<1>(xy);
		return key(x) != -1 && key(y) != -1;
			})  //
		| views::for_each(Join());
}

int main() {

#if false

	std::vector<intint> xs = { {0, 1}, {1, 2}, {2, 3}, {2, 4}, {3, 5} };
	std::vector<intint> ys = { {1, 10}, {2, 20}, {3, 30},
							  {3, 40}, {5, 50}, {6, 60} };

#else
	std::vector<intint> xs = { { 100,200 }, { 200,400 }, { 300, 600 } };
	std::vector<intint> ys = { { 100,300 }, { 200,500 }, { 300, 700 } };
#endif
	

	for_each(join(xs, ys), [](const auto& t) { std::cout << t << std::endl; });	
}