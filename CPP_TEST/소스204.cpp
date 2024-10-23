#include <type_traits>
template <class...> struct type_list; // never instantiated
template <class T>
struct ignore : std::type_identity<T> {
    auto operator=(auto)->ignore<T>;
};
template <template <class> class Pred>
struct find_first_helper {
    template <class T> requires Pred<T>::value
        auto operator=(std::type_identity<T>)->ignore<T>;
    template <class T>
    auto operator=(std::type_identity<T>)->find_first_helper<Pred>;
};
template <class, template <class> class> struct find_first;
template <class... Ts, template <class> class Pred>
struct find_first<type_list<Ts...>, Pred>
    : decltype((find_first_helper<Pred>{} = ... = std::type_identity<Ts>{}))
{ };


int main()
{
    static_assert(
        std::is_same_v<
        typename find_first<
        type_list<char*, float, std::size_t, char*, int>, std::is_integral>::type,
        std::size_t>
        );
}