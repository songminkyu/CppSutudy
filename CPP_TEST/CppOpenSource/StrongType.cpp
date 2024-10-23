#include <iostream>
#include <compare>
/*
C++에서 어떤 entity에 대해, 유일성을 어떻게 보장하는지 이해하니, 쉽게 Strong Type를 만들어낼 수 있군.
어느 순간, 스르르 기본 원리가 떠오르며, 코딩을 다시 전개하니 딱하고!!
*/

template<typename T, typename G>
struct StrongValue {
	T value;

	template<typename F>
	auto operator ==(StrongValue<F, G> const& lhs) const {
		using COMM_TYPE = std::common_type_t<T, F>;
		return (COMM_TYPE)value == (COMM_TYPE)lhs.value;
	}

	template<typename F>
	auto operator <=>(StrongValue<F, G> const& lhs) const {
		using COMM_TYPE = std::common_type_t<T, F>;
		return (COMM_TYPE)value <=> (COMM_TYPE)lhs.value;
	}
};

template<typename T, typename F, typename G>
StrongValue<T, G>& operator+=(StrongValue<T, G>& rhs, StrongValue<F, G> const& lhs) {
	rhs.value += static_cast<T>(lhs.value);
	return rhs;
}

inline namespace {
	using _AGE_TYPE = decltype([] {});
	using _WEIGHT_TYPE = decltype([] {});
}

template<typename T>
using AGE = StrongValue <T, _AGE_TYPE > ;

template<typename T>
using WEIGHT = StrongValue <T, _WEIGHT_TYPE > ;

int main() {
	AGE<int> age{ 10 };
	WEIGHT<int> weight1{ 20 };
	WEIGHT<int> weight2{ 20 };
	WEIGHT<double> d1{ 21.123 };

	// if (age == weight1) { }		// error C2679
	if (weight1 == weight2) {}		// OK
	if (d1 == weight2) {}		    // OK

	d1 += weight2;
	weight2 += d1;
//	age += weight1;					// error C2676

}