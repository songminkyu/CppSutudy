#include <iostream>

/*
atomic constraint�� �����ϸ�
�Ʒ� �ڵ��� ���� �ڿ������� ���صǴ�~
*/
template <unsigned N> constexpr bool Atomic = true;  // constraint ������ �ƴ�.

template <unsigned N> concept           C = Atomic<N>; // atomic constraint #1
template <unsigned N> concept      C_Add1 = C<N + 1>;
template <unsigned N> concept    C_AddOne = C<N + 1>;

template <unsigned M> void f() requires C_Add1<2 * M> {std::cout << "#1\n"; }
template <unsigned M> void f() requires C_AddOne<2 * M> && true{std::cout << "#2\n"; }

template <unsigned N> concept        D = Atomic<N>; // atomic constraint #2
template <unsigned N> concept     D_Add1 = D<N + 1>;

template <unsigned M> void g() requires C_Add1<2 * M> {std::cout << "#3\n"; }
template <unsigned M> void g() requires D_Add1<2 * M> && true{std::cout << "#4\n"; }

int main() {
    f<0>();  // atomic constraint #1���� �߿��ϰ� N->2*M+1�� �����ϰ� ���εȴ�. ���: #2
   // g<0>();  // ERROR:ambiguous atomic constraint #1�� atomic constraint #2���� ���� �߿�. �� �Ұ�. 
}