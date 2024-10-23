#include <vector>
#include <type_traits>

struct Widget
{
	Widget() = default;
	Widget(const Widget &) = default;
	Widget(Widget &&) = default;

};

template<class T>
concept foocept = true;

template<class T>
concept MoveConstructible = requires{
	typename std::enable_if_t<std::is_move_constructible_v<T>>;
};

template<class T>
concept CanAddToInt = requires(T t) {
	{t + 1} -> std::same_as<T>;
	{t + 'a'} -> std::same_as<T>;
};
template<class T>
void foo(T&& arg) requires MoveConstructible<T>&& foocept<T>
{
	std::vector<T> v;
	v.emplace_back(std::forward<T>(arg));
}

int main()
{
	foo(Widget{});

	return 0;
}