#include <iostream>
#include <chrono>

int main() {
    using namespace std::literals;
    using namespace std::chrono;
    static_assert(year_month_day{ sys_days{2017y / January / 0} } == 2016y / December / 31);
    static_assert(year_month_day{ sys_days{2017y / January / 31} } == 2017y / January / 31);
    static_assert(year_month_day{ sys_days{2017y / January / 32} } == 2017y / February / 1);
}