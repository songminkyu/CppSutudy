#include <iostream>
#include <regex>
#include <assert.h>
#include <string>
#include <vector>
using namespace std::string_literals;
using namespace std;

#define C_ALL(X) cbegin(X), cend(X)


//std::regex_token_iterator Example
/*

* std::regex_token_iterator is the utility you are going to use 80% of the time. 
  It has a slight variation as compared to std::regex_iterator. 
  The difference between std::regex_iterator & std::regex_token_iterator is
      - std::regex_iterator points to match results.
      - std::regex_token_iterator points to sub-matches.
* In std::regex_token_iterator, each iterator contains only a single matched result.

*/

bool test1()
{
    const string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
    const regex r(R"((\w+):(\d))");
    // Note: vector<string> here, unlike vector<smatch> as in std::regex_iterator
    const vector<string> full_match{
        sregex_token_iterator{C_ALL(input), r, 0}, // Mark `0` here i.e. whole regex match
        sregex_token_iterator{}
    };
    assert((full_match == decltype(full_match){"ABC:1", "PQR:2", "XYZ:3"}));
    const vector<string> cptr_grp_1st{
        sregex_token_iterator{C_ALL(input), r, 1}, // Mark `1` here i.e. 1st capture group
        sregex_token_iterator{}
    };
    assert((cptr_grp_1st == decltype(cptr_grp_1st){"ABC", "PQR", "XYZ"}));
    const vector<string> cptr_grp_2nd{
        sregex_token_iterator{C_ALL(input), r, 2}, // Mark `2` here i.e. 2nd capture group
        sregex_token_iterator{}
    };
    assert((cptr_grp_2nd == decltype(cptr_grp_2nd){"1", "2", "3"}));
    return EXIT_SUCCESS;
}
bool test2()
{
    const string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
    const regex r(R"((\w+):(\d))");
    const vector<string> inverted{
        sregex_token_iterator{C_ALL(input), r, -1}, // `-1` = parts that are not matched
        sregex_token_iterator{}
    };
    assert((inverted == decltype(inverted){
        "",
            "->   ",
            ";;;   ",
            "<<<",
    }));
    return EXIT_SUCCESS;
}

string transform_pair(string_view text, regex_constants::match_flag_type f = {}) {
    static const auto r = regex(R"((\w+):(\d))");
    return regex_replace(text.data(), r, "$2", f);
}
bool test3()
{
    assert(transform_pair("ABC:1, PQR:2"s) == "1, 2"s);
    // Things that aren't matched are not copied
    assert(transform_pair("ABC:1, PQR:2"s, regex_constants::format_no_copy) == "12"s);
    return EXIT_SUCCESS;
}


int main() {
    test1();
    test2();
    test3();
}
