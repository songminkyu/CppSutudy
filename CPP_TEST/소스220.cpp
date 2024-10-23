#include <iostream>
#include <utility>

template<class T1, class T2, auto size1, auto size2>
void assign(T1(&rhs)[size1], T2(&lhs)[size2]) {
    [&] <auto... idx>(std::index_sequence<idx...>) {
        ((rhs[idx] = lhs[idx]), ...);
    }(std::make_index_sequence< (size1 > size2) ? size2 : size1 >{});
}

int main() 
{
    int rhs[] = { 1,2 };
    int lhs[] = { 0,0,0 };
    assign(lhs, rhs);
    for (auto&& mitem : lhs) {
        std::cout << mitem << std::endl;
    }
}