#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

template<class T, class Container>
class Index_iterator {
protected:
    Container* container = nullptr;
    T          delimiter = {};
    std::size_t cnt = 0;
public:
    using iterator_category = std::output_iterator_tag;
    using        value_type = void;
    using   difference_type = ptrdiff_t;
    using           pointer = void;
    using         reference = void;
    using    container_type = Container;

    constexpr Index_iterator() noexcept = default;
    constexpr explicit Index_iterator(Container& cont, T del) :container{ &cont }, delimiter{ del } {}

    constexpr Index_iterator& operator=(const T& value) {
        do {
            if (delimiter != value) break;
            container->push_back(cnt);
        } while (false);
        ++cnt;
        return *this;
    }
    constexpr Index_iterator& operator=(T&& value) { return *this = value; }
    constexpr Index_iterator& operator*() { return *this; }
    constexpr Index_iterator& operator++() { return *this; }
    constexpr Index_iterator  operator++(int) { return *this; }
};

int main() {
    int a[] = { 1,2,3,1,2,45,1,9 };

    std::vector<std::size_t> item_con;
    Index_iterator items{ item_con, 1 };

    using namespace std::ranges;
    copy(a, items);
    for (auto&& item : item_con) std::cout << item << " ";
}