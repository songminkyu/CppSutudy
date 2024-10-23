#include <utility> // index_sequence
#include <iostream> // for demo only

template<typename, std::size_t> concept Any = true;
template <class... Args>
auto invoke_with_last_arg(Args... args) {
    return[&]<std::size_t... I>(std::index_sequence<I...>) {
        return [](Any<I> auto..., auto last, auto f) {
            return f(last);
        }(args...); 
    }(std::make_index_sequence<sizeof...(Args) - 2>{});
}
template <class... Pack>
void demo(Pack... args) {
    invoke_with_last_arg(args...,
        [](auto last_arg) { std::cout << last_arg << std::endl; }
    );
}
int main() { 

    demo(3.14, 42, "hello world"); 
}