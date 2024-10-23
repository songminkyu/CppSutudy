#include <utility> // std::forward
#include <iostream>

template <class Lambda>
struct recursive_lambda : Lambda {
    template <class... Args>
    auto operator()(Args&&... args) {
        return this->Lambda::operator()(*this, (Args&&)args...);
    }
};
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