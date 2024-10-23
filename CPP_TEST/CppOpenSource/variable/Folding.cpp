#include <iostream>

template <int...> struct values { };

template <int... Is>
void call(auto&& f, values<Is...>) 
{
    (f(Is), ...);
}

template <int... Is>
void call_reverse(auto&& f, values<Is...>) 
{
    int sink;
    ((f(Is), sink) = ... = 0);
}

int main()
{
    const auto print = [](int x) { std::cout << x; };

    call(print, values<0, 1, 2, 3, 6>{});
    std::cout << '\n';
    call_reverse(print, values<0, 1, 2, 3, 6>{});
}