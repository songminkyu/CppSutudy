#include <iostream>
#include <chrono>

/*
https://godbolt.org/z/hen3Yasjb
2021년 모든 달의 마지막 일요일을 얻어내라.
*/

template<class... ARGS>
std::basic_ostream<ARGS...>& operator<<(std::basic_ostream<ARGS...>& ct, std::chrono::year_month_weekday_last& ld) {
    std::chrono::year_month_day d{ std::chrono::sys_days{ld} };
    ct << (int)d.year() << '.' << ' ' << (unsigned int)d.month() << '.' << ' ' << static_cast<unsigned>(d.day());
    return ct;
}

int main() {
    using namespace std::literals;
    using namespace std::chrono;

    auto t1 = 2021y / month{ 1 } / Sunday[last];
    auto t2 = 2021y / month{ 12 } / Sunday[last];
    for (; t1 != t2; t1 += months{ 1 }) {
        std::cout << t1 << '\n';
    }
}

/*
2015. 1. 31
2015. 2. 28
2015. 3. 31
2015. 4. 30
2015. 5. 31
2015. 6. 30
2015. 7. 31
2015. 8. 31
2015. 9. 30
2015. 10. 31
2015. 11. 30
2015. 12. 31

*/