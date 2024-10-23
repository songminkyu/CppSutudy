#include <iostream>
#include <tuple>
#include <algorithm>
#include <ranges>    

using namespace std;

int main() {
   
    pair<int, std::string_view> pairs[] = { {2, "foo"}, {1, "bar"}, {0, "baz"} };
    ranges::sort(pairs, ranges::less{}, [](auto const& p) { return p.first; });
    for (auto&& [first, second] : pairs) {
        cout << first << "," << second << endl;
    }
    return 0;
}