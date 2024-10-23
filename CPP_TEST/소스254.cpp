#include <concepts>
#include <iostream>
#include <typeinfo> 

/*
* 
std::copyable for copyable types

std::copyable helps you to ensure that only such types are accepted whose instances can be copied. 
std::copyable object must be copy constructible, assignable and movable.

*/
class NonMovable {
public:
	NonMovable() = default;
	~NonMovable() = default;

	NonMovable(const NonMovable&) = default;
	NonMovable& operator=(const NonMovable&) = default;

	NonMovable(NonMovable&&) = delete;
	NonMovable& operator=(NonMovable&&) = delete;
};

class NonCopyable {
public:
	NonCopyable() = default;
	~NonCopyable() = default;

	NonCopyable(const NonCopyable&) = default;
	NonCopyable& operator=(const NonCopyable&) = default;

	NonCopyable(NonCopyable&&) = delete;
	NonCopyable& operator=(NonCopyable&&) = delete;
};

class Copyable {
public:
	Copyable() = default;
	~Copyable() = default;

	Copyable(const Copyable&) = default;
	Copyable& operator=(const Copyable&) = default;

	Copyable(Copyable&&) = default;
	Copyable& operator=(Copyable&&) = default;
};

template <typename T>
void fun(T t) requires std::copyable<T> {
	std::cout << typeid(t).name() << " is copyable\n";
}

int main() {
	NonMovable nm;
	//   fun(nm); // error: use of function 'void fun(T) requires  copyable<T> [with T = NonMovable]' with unsatisfied constraints
	NonCopyable nc;
	//   fun(nc); // error: use of function 'void fun(T) requires  copyable<T> [with T = NonCopyable]' with unsatisfied constraints
	Copyable c;
	fun(c);
}

/*
As you can see in the above example, class NonMovable doesn¡¯t satisfy the concept as its move assignment and move constructor are deleted.

For NonCopiable, it¡¯s a similar case, but while the move semantics are available, it lacks the copy assignment and the copy constructor.

Finally, Copyable class defaults all the 5 special member functions and as such, it satisfies the concept of std::copyable.

*/