#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <compare>
#include <ranges>

struct A {
    int         val{ };
    std::string name{ };

    friend auto operator<=>(const A& lhs, const A& rhs) { return lhs.val <=> rhs.val; }
    friend constexpr bool operator==(const A& lhs, const A& rhs) {
        return (lhs.val == rhs.val) && (lhs.name == rhs.name);
    }

    friend
        std::ostream& operator<< (std::ostream& ct, const A& rhs) {
        ct << '[' << rhs.val << ',' << rhs.name << ']';
        return ct;
    }
};

int main() {
    using namespace std::ranges;
    std::vector<A> data{ {1,"one1"}, {1,"one2"}, {10,"ten1"}, {10,"ten2"} };

    auto [m1, m2] = minmax(data);
    std::cout << m1 << '\n';
    std::cout << m2 << '\n';
}