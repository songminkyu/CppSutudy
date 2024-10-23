#include <type_traits>
#include <optional>
#include <iostream>


template <typename T>
concept trivial_value_type
= std::is_trivial_v<typename T::value_type>;
template <typename... Ts>
requires (trivial_value_type<Ts> || ...)
void fun(Ts... v)
{
    std::cout << " 2" << std::endl;
    return;
}

int main()
{
    std::optional<int> oi{};
    int i{};
    fun(i, oi);
       
    return 0;
}
