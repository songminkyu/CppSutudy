#include <type_traits> // type_identity
#include <utility> // integer_sequence

//https://twitter.com/The_Whole_Daisy?fbclid=IwAR2hI-gd3rhfJwfip_tey6kIkQEsH7fwlCbSNI1CAXY30dlEQ7_zTDy2Rh0

template <class Seq> struct inclusive_scan;
template <class T, T... ts>
struct inclusive_scan<std::integer_sequence<T, ts...>>
    : decltype([]<std::size_t... Idxs>(std::index_sequence<Idxs...>) {
    return std::type_identity < std::integer_sequence < T,
        [](auto Idx) { return (0 + ... + (Idxs <= Idx ? ts : 0)); }(Idxs)...
        >> {};
}(std::make_index_sequence<sizeof...(ts)>{})) {};



int main()
{
 
    bool r = std::is_same_v<typename inclusive_scan<std::index_sequence<1, 2, 3, 4, 5>>::type, std::index_sequence<1, 3, 6, 10, 15>>();


}