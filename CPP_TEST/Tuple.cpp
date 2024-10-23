#include <utility>
#include <cstdio>
#include <iostream>

/*
tuple이 이렇게 쉽게 구현 가능해지는군 ㅋㅋ.
람다 객체에 ... 구문이 가능해지면서 기적에 가까운 일이~
기존 라이브러리 구현보다 더 훌룡해 보이네. 캬~.
컴파일 시간 계산까지..
*/
template <typename ... Ts>
constexpr auto tuple(Ts&& ... ts)
{
	return[...ts = std::forward<Ts>(ts)](auto&& f) { return f(ts...); };
}

template <unsigned I, typename T, typename ... Ts>
constexpr auto get_val(const T& t, const Ts& ... ts)
{
	if constexpr (I == 0) return t;
	else return get_val<I - 1>(ts...);
}

template <unsigned I, typename T>
constexpr decltype(auto) get(T&& t)
{
	return t([](auto&& ... vs) { return get_val<I>(std::forward<decltype(vs)>(vs)...); });
}

template <typename T>
constexpr auto size(T&& t)
{
	return t([](const auto& ... ts) { return sizeof...(ts); });
}

int main()
{
	constexpr auto t = tuple(1, "foo", 3.14);
	constexpr auto n = size(t);
	std::cout << get<0>(t) << std::endl;
	std::cout << get<1>(t) << std::endl;
	std::cout << get<2>(t) << std::endl;

	return get<n - 1>(t) - get<0>(t);
}