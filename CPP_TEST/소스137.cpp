#include <iostream>
#include <regex>
#include <assert.h>
#include <string>
#include <vector>
using namespace std::string_literals;

/*
std::regex_iterator Example

* std::regex_iterator is helpful when you need very detailed information about matched & sub-matches.

* Earlier(in C++11), there was a limitation that using std::regex_interator is not allowed to be called with a temporary regex object.
  Which has been rectified with overload from C++14.
*/

#define C_ALL(X) cbegin(X), cend(X)
int main() {
    const std::string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
    const std::regex r(R"((\w+):(\d))");
    const std::vector<std::smatch> matches{
        std::sregex_iterator{C_ALL(input), r},
        std::sregex_iterator{}
    };
    assert(matches[0].str(0) == "ABC:1"
        && matches[0].str(1) == "ABC"
        && matches[0].str(2) == "1");
    assert(matches[1].str(0) == "PQR:2"
        && matches[1].str(1) == "PQR"
        && matches[1].str(2) == "2");
    assert(matches[2].str(0) == "XYZ:3"
        && matches[2].str(1) == "XYZ"
        && matches[2].str(2) == "3");
    return EXIT_SUCCESS;
}

