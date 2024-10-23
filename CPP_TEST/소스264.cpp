#include <iterator>
#include <algorithm>
#include <iostream>
#include <ranges>

template<class CharT>
std::size_t txt_len(const CharT* s)
{
    using namespace std::ranges;
    return find(s, std::unreachable_sentinel, CharT{}) - s;
}

int main() {
    std::cout
        << txt_len("The quick brown fox jumps over the lazy dog.") << '\n';
}