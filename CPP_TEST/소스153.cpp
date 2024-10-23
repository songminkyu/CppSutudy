#include <iostream>
#include <vector>
#include <compare>
using namespace std;


//CRTP 와 관련 없는거같음.

template <class derived>
struct compare {};
struct value : compare<value> {
    int m_x;
    value(int x) : m_x(x) {}
    bool operator < (const value& rhs) const { return m_x < rhs.m_x; }
};
template <class derived>
bool operator > (const compare<derived>& lhs, const compare<derived>& rhs) {
    // static_assert(std::is_base_of_v<compare<derived>, derived>); // Compile time safety measures
    return (static_cast<const derived&>(rhs) < static_cast<const derived&>(lhs));
}
/*  Same goes with other operators
    == :: returns !(lhs < rhs) and !(rhs < lhs)
    != :: returns !(lhs == rhs)
    >= :: returns (rhs < lhs) or (rhs == lhs)
    <= :: returns (lhs < rhs) or (rhs == lhs)
*/


struct value_cpp20 {
    int m_x;
    value_cpp20(int x) : m_x(x) {}
    std::weak_ordering operator<=>(const value_cpp20& rhs) const = default;
};
int main() {
    value v1{ 5 }, v2{ 10 };
    cout << boolalpha << "v1 > v2: " << (v1 > v2) << '\n';

    value_cpp20 v3{ 5 }, v4{ 10 };
    cout << boolalpha << "v3 > v4: " << (v3 < v4) << '\n';


    return EXIT_SUCCESS;
}