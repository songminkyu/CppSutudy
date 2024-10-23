#include <iostream>
#include <regex>
#include <assert.h>
#include <string>
#include <vector>
using namespace std::string_literals;
using namespace std;

/*
Splitting a String With Delimiter

Although std::strtok is best suitable & optimal candidate for such a task. 
But just to demonstrate how you can do it with regex:

*/
#define C_ALL(X) cbegin(X), cend(X)
vector<string> split(const string& str, string_view pattern) {
    const auto r = regex(pattern.data());
    return vector<string>{
        sregex_token_iterator(C_ALL(str), r, -1),
            sregex_token_iterator()
    };
}
int main() {
    assert((split("/root/home/vishal", "/")
        == vector<string>{"", "root", "home", "vishal"}));
    return EXIT_SUCCESS;
}
