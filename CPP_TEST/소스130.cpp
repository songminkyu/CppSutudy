#include <iostream>
#include <regex>
#include <assert.h>

// 자세한 사항은 아래 URL 참조
//std::regex & std::regex_error Example

/*
* You see! I am using raw string literals. You can also use the normal string. 
But, in that case, you have to use a double backslash for an escape sequence.

*The current implementation of std::regex is slow(as it needs regex interpretation & data 
structure creation at runtime), bloated and unavoidably require heap allocation(not allocator-aware).
So, beware if you are using std::regex in a loop(see C++ Weekly – Ep 74 – std::regex optimize by Jason Turner).
Also, there is only a single member function that I think could be of use is 
std::regex::mark_count() which returns a number of capture groups.

* Moreover, if you are using multiple strings to create a regex pattern at run time. 
Then you may need exception handling i.e. std::regex_error to validate its correctness.

*/
int main() {
    try {
        static const auto r = std::regex(R"(\)"); // Escape sequence error       
    }
    catch (const std::regex_error& e) {
        assert(strcmp(e.what(), "Unexpected end of regex when escaping.") == 0);
        assert(e.code() == std::regex_constants::error_escape);
    }
    return EXIT_SUCCESS;
}
