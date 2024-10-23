

/*
���� chrono�� C++20 ���忡 �°� ������ �ȵ� ��������(fmt�� �Ϸ�ǰ� �� ���� �ö󰡴� ������ �Ϻ� �����ؼ� ������ �ܰ迡 �Ϸ�ɵ�), �ӽ� �ڵ�����~
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