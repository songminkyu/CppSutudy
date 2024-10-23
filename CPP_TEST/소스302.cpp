#include <iostream>
#include <tuple>

template<class> struct FnDecomp;

template<class R, class ... Args>
struct FnDecomp<R(Args...)> {
	using RETURN_TYPE = R;

	using _ = std::tuple<Args...>;

	template<std::size_t Idx>
	using ARG_TYPE = std::tuple_element_t<Idx, _>;

	static constexpr const std::size_t ARG_COUNT = sizeof...(Args);

};

template<class FN>
std::ostream& operator<<(std::ostream& cnt, FnDecomp<FN>&&) {
	using FN_INFO = FnDecomp<std::remove_reference_t<FN>>;
	cnt << "return:" << typeid(typename FN_INFO::RETURN_TYPE).name();

	[&] <auto... Is>(std::index_sequence<Is...>) {
		(
			cnt << ... << ((
				cnt << "\narg[" << Is << "]:",
				typeid(typename FN_INFO::template ARG_TYPE<Is>).name()
				))
			);

	}(std::make_index_sequence<FN_INFO::ARG_COUNT>{});

	return cnt;
}

template<class FN>
void function_info(FN&&) {
	using FN_INFO = FnDecomp<std::remove_reference_t<FN>>;
	std::cout << FN_INFO{};
}

void test(int, float, void*) {};


int main() {
	function_info(test);
	return EXIT_SUCCESS;
}
