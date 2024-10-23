#include <iostream>
template <unsigned N> constexpr bool Atomic = true;  // constraint 구문이 아님.

template <unsigned N> concept           C = Atomic<N>; // atomic constraint #1
template <unsigned N> concept        Add1 = C<N + 1>;

template <unsigned N> void f2() requires Add1<2 * N>{ std::cout << "#1\n"; }
template <unsigned N> void f2() requires Add1<N * 2> && true{ std::cout << "#2\n"; }


int main() {
    //f2<0>();
    // ambiguous
    // 상단 f2: atomic constraint #1에서 발원 N-> 2*N +1
    // 하단 f2: atomic constraint #1에서 발원 N-> N*2 +1
}