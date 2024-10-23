#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>

template<class charT, class... Ts>
struct istream_container {
    std::basic_istream<charT, Ts...>& fp;

    istream_container(std::basic_istream<charT, Ts...>& fp) :fp{ fp } {}

    auto begin() {
        fp.clear();
        fp.seekg(0);
        return std::istreambuf_iterator<charT>(fp);
    }

    auto end() {
        return std::istreambuf_iterator<charT>();
    }
};

int main() {

    std::ifstream fp("test.txt");
    istream_container container(fp);
    std::string src(begin(container), end(container));

    for (auto&& item : container) {
        std::cout << item;
    }
}

