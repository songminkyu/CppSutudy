#include <iostream>
/*
class template deduction guide를 aggregate type에도 적용할 수 있습니다.
꽤나 유용하면서도 앞으로 많은 상상력이 여기에서부터 출발할듯
*/
template<class T, std::size_t N>
struct AT {
    T data[N];
    void print() {
        for (auto&& mitem : data) {
            std::cout << mitem << std::endl;
        }
    }
};

int main() {
    AT at{ {1,2,3,4,5} };
    at.print();
}