#include <iostream>
#include <type_traits>

struct Vector2D {};
struct B :Vector2D {
	void length() { std::cout << "#1111" << std::endl; };
};

template<typename derived, typename base>
concept isBase = std::is_base_of_v<std::remove_reference_t<base>, std::remove_reference_t<derived>>;


template<typename vector>
concept A = requires(vector vec) {
	{vec.length()};
	{vec} noexcept ->isBase<Vector2D>;
};

template<typename T> requires A<T>
void test() {}

int main() {
	test<B>();
}