#include <iostream>
#include <regex>
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>

using namespace std::string_literals;
using namespace std;


string join(const vector<string>& words, const string& delimiter) {
    return accumulate(next(begin(words)), end(words), words[0],
        [&delimiter](string& p, const string& word)
        {
            return p + delimiter + word;
        });
}
vector<string> lines_containing(const string& file, const vector<string>& words) {
    auto prefix = "^.*?\\b("s;
    auto suffix = ")\\b.*$"s;
    //  ^.*?\b(one|two|three)\b.*$
    const auto pattern = move(prefix) + join(words, "|") + move(suffix);
    ifstream        infile(file);
    vector<string>  result;
    for (string line; getline(infile, line);) {
        if (regex_match(line, regex(pattern))) {
            result.emplace_back(move(line));
        }
    }
    return result;
}
int main() {
    assert((lines_containing("test.txt", { "one","two" })
        == vector<string>{"This is one",
        "This is two"}));
    return EXIT_SUCCESS;
}
/* test.txt
This is one
This is two
This is three
This is four
*/
