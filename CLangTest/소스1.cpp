#include <iostream>
#include <functional>
#include <concepts>

template< class F, class... Args >
concept invocable =
requires(F && f, Args &&... args) {
	std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
};

struct A {
	A& operator <<(invocable<A&> auto&& fp) {
		return fp(*this);
	}

	void set(int v) { value_ = v; }
private:
	int value_{};
};

auto test(int value) {
	auto fn = [value](A& a)->A& {
		a.set(value);
		return a;
	};
	return fn;
}

int main() {
	A a{};
	a << test(10);
}
