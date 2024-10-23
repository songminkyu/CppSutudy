#include <utility> // integral_constant, index_sequence, forward
#include <iostream> // for demo only
template <class... Lambdas>
struct MyTupleImpl : Lambdas... { using Lambdas::operator()...; };

template <class... Ls> 
MyTupleImpl(Ls...)->MyTupleImpl<Ls...>;


template <std::size_t... Idxs, class... Ts>
constexpr auto make_my_tuple_impl(std::index_sequence<Idxs...>, Ts&&... ts) {
    return MyTupleImpl{
      [t = ts](std::integral_constant<std::size_t, Idxs>)
        mutable -> std::decay_t<Ts>& { return t; }... };
}
template <class... Ts>
constexpr auto make_my_tuple(Ts&&... ts) {
    return make_my_tuple_impl(std::index_sequence_for<Ts...>{},
        std::forward<Ts>(ts)...);
}
template <std::size_t I, class... Lambdas>
constexpr auto& get(MyTupleImpl<Lambdas...>& t) {
    return t(std::integral_constant<std::size_t, I>{});
}
int main() {
    auto t = make_my_tuple(42, "hello", 3.14, "world");
    std::cout << get<1>(t) << " " << get<3>(t) << std::endl;
}