#include <iostream>
#include <chrono>

template<class... ARGS>
std::basic_ostream<ARGS...>& operator<<(std::basic_ostream<ARGS...>& ct, std::chrono::year_month_day_last& d) {
    ct << (int)d.year() << '.' << ' ' << (unsigned int)d.month() << '.' << ' ' << static_cast<unsigned>(d.day());
    return ct;
}

int main() {
    using namespace std::literals;
    using namespace std::chrono;

    auto t1 = 2015y / month{ 1 } / last;
    auto t2 = 2015y / month{ 12 } / last;
    for (; t1 <= t2; t1 += months{ 1 }) {
        std::cout << t1 << '\n';
    }
}