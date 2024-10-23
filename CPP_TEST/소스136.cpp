#include <iostream>
#include <regex>
#include <assert.h>
#include <string>

//std::regex_match Example

/*
* Short & sweet example that you may always find in every regex book is email validation. 
  And that is where our std::regex_match function fits perfectly.

 * I know this is not full proof email validator regex pattern. But my intention is also not that.

 * Rather you should wonder why I have used std::regex_match! not std::regex_search! The rationale 
   is simple std::regex_match matches the whole input sequence.
 
 * Also, Noticeable thing is static regex object to avoid constructing (¡°compiling/interpreting¡±) 
   a new regex object every time the function entered.

 * The irony of above tiny code snippet is that it produces around 30k lines of assembly that too with -O3 flag.
   And that is ridiculous. But don¡¯t worry this is already been brought to the ISO C++ community. 
   And soon we may get some updates. Meanwhile, we do have other alternatives (mentioned at the end of this article).

*/

bool is_valid_email_id(std::string_view str) {
    static const std::regex r(R"(\w+@\w+\.(?:com|in))");
    return std::regex_match(str.data(), r);
}
int main() {
    assert(is_valid_email_id("vishalchovatiya@ymail.com") == true);
    assert(is_valid_email_id("@abc.com") == false);
    return EXIT_SUCCESS;
}