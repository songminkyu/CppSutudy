#include <iostream>
#include <regex>
#include <assert.h>
#include <string>

using namespace std::string_literals;
//Difference Between std::regex_match & std::regex_search?

/*
*You might be wondering why do we have two functions doing almost the same work? 
 Even I had the doubt initially.But, after reading the description provided by 
 cppreference over and over. I found the answer. And to explain that answer, 
 I have created the example (obviously with the help of StackOverflow):

* std::regex_match only returns true when the entire input sequence has been matched, 
  while std::regex_search will succeed even if only a sub-sequence matches the regex.

*/

int main() {
    const std::string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
    const std::regex r(R"((\w+):(\w+);)");
    std::smatch m;
    assert(regex_match(input, m, r) == false);
    assert(regex_search(input, m, r) == true && m.ready() == true && m[1] == "PQR");
    return EXIT_SUCCESS;
}