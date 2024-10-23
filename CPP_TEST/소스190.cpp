



#include <utility> // std::forward
#include <iostream>


/*
For safety and sanity in a real-world use of this, you should probably use private
inheritance to avoid having the base type call operator participate in overload
resolution: https://godbolt.org/z/WEc9hh. I omitted this for brevity,
but this also means that you can no longer treat recursive_lambda as an aggregate,
so you need an explicit constructor. The class template definition becomes:
*/


template <class Lambda>
struct recursive_lambda : private Lambda {
    constexpr explicit recursive_lambda(Lambda l)
        : Lambda(std::move(l)) { }
    template <class... Args>
    auto operator()(Args&&... args) {
        return this->Lambda::operator()(*this,
            std::forward<Args>(args)...);
    }
};

//This does mean, though, that you no longer need the deduction guide.


template <class Lambda>
recursive_lambda(Lambda)->recursive_lambda<Lambda>;

int test() {
    auto fibonacci = recursive_lambda{
      [](auto& self, int n) -> int {
        if (n < 2) { return n; }
        else { return self(n - 1) + self(n - 2); }
      }
    };
    return fibonacci(10);
}

int main()
{
    std::cout << test() << std::endl;
}