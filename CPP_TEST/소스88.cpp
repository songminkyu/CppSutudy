#include <iostream>
#include <functional>
#include <concepts>

template< class F, class... Args >
concept invocable =
requires(F && f, Args &&... args) {
	std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
};

struct A {
#if true
	template<class T> requires invocable<T,A&>
	A& operator <<(T fp) {			
		return fp(*this);
	}
#else
	A& operator <<(invocable<A&> auto&& fp) {
		return fp(*this);
	}
#endif

	void set(int v) { value_ = v; }
public:
	auto get() { return value_; };
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
void (*fp)(int);
int main() {
	A a{};
	a << test(10);
	std::cout << a.get();
}
