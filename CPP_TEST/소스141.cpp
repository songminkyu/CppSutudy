#include <iostream>
#include <regex>
#include <assert.h>
#include <string>
#include <vector>
using namespace std::string_literals;
using namespace std;

/*
Trim Whitespace From a String
http://www.vishalchovatiya.com/regex-c/?fbclid=IwAR3A84GNW-dD2m_3L-44MmxED5ES7kmQQd_1I6AuWiQL2jVNFiJYST_eVtU

*/
string trim(string_view text) {
    static const auto r = regex(R"(\s+)");
    return regex_replace(text.data(), r, "");
}
int main() {
    assert(trim("12   3 4      5"s) == "12345"s);
    return EXIT_SUCCESS;
}
