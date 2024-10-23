#include <iostream>
#include <tuple>

template<class... Ts1, class... Ts2>
auto make_tuple_cat(std::tuple<Ts1...>& ts1, std::tuple<Ts2...>& ts2) {
	auto tuple_cat = [&]<std::size_t... Is1, std::size_t... Is2>
		(std::index_sequence<Is1...>, std::index_sequence<Is2...>)
	{
		std::tuple<Ts1..., Ts2...> dat{ std::get<Is1>(ts1)..., std::get<Is2>(ts2)... };
		return dat;
	};
	return tuple_cat(
		std::make_index_sequence<sizeof...(Ts1)>{},
		std::make_index_sequence<sizeof...(Ts2)>{});
}

template<class... Ts>
void print_tuple(std::tuple<Ts...>& ts) {
	auto tuple_print = [&]<std::size_t... Is>
		(std::index_sequence<Is...>)
	{
		((std::cout <<
			typeid(Ts).name() << ':'
			<< std::get<Is>(ts) << '\n'), ...);
	};
	tuple_print(std::make_index_sequence<sizeof...(Ts)>{});
}

int main() { 
	std::tuple<int, long> d1{ 1,2 };
	std::tuple<float, double, int> d2{ 3.5f, 4.3, 1 };
	auto f = make_tuple_cat(d1, d2);
	print_tuple(f);
}