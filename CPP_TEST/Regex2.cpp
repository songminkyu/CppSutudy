#include <iostream>
#include <regex>

int main()
{
    auto const regex = std::regex("(my|your) regex");

    auto const myText = std::string("A piece of text that contains my regex.");
    auto searchResults = std::smatch{};
    bool const myTextContainsRegex = std::regex_search(myText, searchResults, regex);

    std::cout << "position in searched text: " << searchResults.prefix().length() << '\n';
    // my 라는 단어가 몇번째 위치에 있는지 확인할수 있음.

}