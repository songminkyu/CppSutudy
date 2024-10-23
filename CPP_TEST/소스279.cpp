

/*
아직 chrono가 C++20 스펙에 맞게 조정이 안된 상태지만(fmt가 완료되고 그 위에 올라가는 개념이 일부 존재해서 마지막 단계에 완료될듯), 임시 코딩으로~
*/

#include <iostream>
#include <chrono>

template<class... ARGS>
std::basic_ostream<ARGS...>& operator<<(std::basic_ostream<ARGS...>& ct, std::chrono::year_month& d) {
    ct << (int)d.year() << 'y' << ' ' << (unsigned int)d.month() << 'm';
    return ct;
}

int main() {
    using namespace std::literals;
    using namespace std::chrono;

    auto t = 2020y / month{ 1 } - months{ 2 };
    std::cout << t;
}