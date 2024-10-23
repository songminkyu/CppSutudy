#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

struct A {
    int a;
};

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& ostr, const A& datum) {
    ostr.write((const char*)&datum.a, sizeof(datum.a));
    return ostr;
}

std::basic_istream<char>& operator>>(std::basic_istream<char>& istr, A& datum) {
    istr.read((char*)&datum.a, sizeof(datum.a));
    return istr;
}

int main() {
    {
        std::ofstream fp(R"(d:\123123123.txt)", std::ios::binary);
        std::vector<A> data;
        for (int i = 1; i < 5; ++i) {
            data.emplace_back(A{ i });
        }
        std::copy(std::begin(data), std::end(data), std::ostream_iterator<A>{fp});
    }

    {
        std::ifstream fp(R"(d:\123123123.txt)", std::ios::binary);//
        if (!fp) {
            std::cout << "file is not founded\n";
            return 0;
        }

        std::vector<A> data{
            std::istream_iterator<A>{fp},
            std::istream_iterator<A>{}
        };

        for (auto&& datum : data) std::cout << datum.a << std::endl;
    }
}
