#include <iostream>
#include <utility>

template<std::size_t N1, class T>
struct assign {
	T value_{};
	assign& operator=(const T& v) { value_ = v; return *this; }
	operator T() const { return value_; }

	template<std::size_t N2>
	decltype(auto) get() requires (N1 == N2)
	{
		return (value_);
	}
};

template<class... TS>
auto make() {
	return
		[]<std::size_t... Idxs>(std::index_sequence<Idxs...>) {
		struct _ : assign<Idxs, TS>... {
			using assign<Idxs, TS>::operator=...;
			using assign<Idxs, TS>::get...;
		} a{};

		return a;
	}(std::make_index_sequence<sizeof...(TS)>{});
}

int main() {
	auto obj = make<int, float, double>();
	obj = 1;
	obj = 2.4;
	obj = 3.5f;
	std::cout << obj.get<0>() << "\n" << obj.get<1>() << "\n" << obj.get<2>();
}