#include <type_traits>
template <class...> struct type_list;
template <class, class = void> struct analyze_list;
template <> struct analyze_list<type_list<>> { // recursive base case
	static constexpr auto int_count = 0;
	static constexpr auto float_count = 0;
	static constexpr auto other_count = 0;
};
template <class T, class... Ts>
struct analyze_list<type_list<T, Ts...>, std::enable_if_t<std::is_integral_v<T>>>
	: analyze_list<type_list<Ts...>> {
	using base_t = analyze_list<type_list<Ts...>>;
	static constexpr auto int_count = analyze_list<type_list<Ts...>>::int_count + 1;
};
template <class T, class... Ts>
struct analyze_list<type_list<T, Ts...>, std::enable_if_t<std::is_floating_point_v<T>>>
	: analyze_list<type_list<Ts...>> {
	static constexpr auto float_count = analyze_list<type_list<Ts...>>::float_count + 1;
};
template <class> struct analyze_list_helper;
template <class T, class... Ts>
struct analyze_list_helper<type_list<T, Ts...>> : analyze_list<type_list<Ts...>> {
	static constexpr auto other_count = analyze_list<type_list<Ts...>>::other_count + 1;
};
// Notice: Unspecialized! No need for !is_floating_point_v<...> && !is_integral_v<...>
template <class List, class>
struct analyze_list : analyze_list_helper<List> {};
using demo_list = type_list<int, float, double, char, int&, char**>;

int main()
{
	static_assert(analyze_list<demo_list>::int_count == 2);
	static_assert(analyze_list<demo_list>::float_count == 2);
	static_assert(analyze_list<demo_list>::other_count == 2);
}