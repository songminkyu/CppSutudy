#include <iostream>
#include <regex>
#include <assert.h>
#include <string>
#include <vector>
using namespace std::string_literals;
using namespace std;
#define C_ALL(X) cbegin(X), cend(X)
/*

* You see in 2nd call of transform_pair, we passed flag std::regex_constants::format_no_copy which suggest
  do not copy thing that isn¡¯t matched. There are many such useful flags under std::regex_constant.

* Also, we have constructed the fresh string holding the results. But what if we do not want a new string. 
  Rather wants to append the results directly to somewhere(probably container or stream or already existing string). 
  Guess what! the standard library has covered this also with overloaded std::regex_replace as follows:

*/
string transform_pair(string_view text, regex_constants::match_flag_type f = {}) {
    static const auto r = regex(R"((\w+):(\d))");
    return regex_replace(text.data(), r, "$2", f);
}
int main() {
    assert(transform_pair("ABC:1, PQR:2"s) == "1, 2"s);
    // Things that aren't matched are not copied
    assert(transform_pair("ABC:1, PQR:2"s, regex_constants::format_no_copy) == "12"s);


    const string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
    const regex r(R"(-|>|<|;| )");
    // Prints "ABC:1     PQR:2      XYZ:3   "
    regex_replace(ostreambuf_iterator<char>(cout), C_ALL(input), r, " ");
  
    return EXIT_SUCCESS;
}
