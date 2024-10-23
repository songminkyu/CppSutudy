
#include <iostream>
#include <regex>
#include <assert.h>
#include <string>

using namespace std::string_literals;


/*

std::regex_search Example

* smatch is the specializations of std::match_results that stores the information about matches to be retrieved.
*/

int main() {
    const std::string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
    const std::regex r(R"((\w+):(\w+);)");
    std::smatch m;
    if (regex_search(input, m, r)) {
        assert(m.size() == 3);
        assert(m[0].str() == "PQR:2;");                // Entire match
        assert(m[1].str() == "PQR");                   // Substring that matches 1st group
        assert(m[2].str() == "2");                     // Substring that matches 2nd group
        assert(m.prefix().str() == "ABC:1->   ");      // All before 1st character match
        assert(m.suffix().str() == ";;   XYZ:3<<<");   // All after last character match
        // for (string &&str : m) { // Alternatively. You can also do
        //     cout << str << endl;
        // }
    }
    return EXIT_SUCCESS;
}