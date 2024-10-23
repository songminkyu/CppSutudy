#include <iostream>
#include <chrono>

template<class... ARGS>
std::basic_ostream<ARGS...>& operator<<(std::basic_ostream<ARGS...>& ct, std::chrono::year_month_day& d) {
    ct << (int)d.year() << '.' << ' ' << (unsigned int)d.month() << '.' << ' ' << static_cast<unsigned>(d.day());
    return ct;
}

int main() {
    using namespace std::literals;
    using namespace std::chrono;

    auto t1 = 2015y / month{ 1 };
    auto t2 = 2015y / month{ 12 };
    for (; t1 <= t2; t1 += months{ 1 }) {
        auto last_day = year_month_day{ t1 / last };
        std::cout << last_day << '\n';
    }
}