#include <iostream>
#include <regex>
#include <assert.h>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <filesystem>

using namespace std::string_literals;
using namespace std;


namespace fs = std::filesystem;
vector<fs::directory_entry> find_files(const fs::path& path, string_view rg) {
    vector<fs::directory_entry> result;
    regex r(rg.data());
    copy_if(
        fs::recursive_directory_iterator(path),
        fs::recursive_directory_iterator(),
        back_inserter(result),
        [&r](const fs::directory_entry& entry) {
            return fs::is_regular_file(entry.path()) &&
                regex_match(entry.path().filename().string(), r);
        });
    return result;
}
int main() {
    const auto dir = fs::temp_directory_path();
    const auto pattern = R"(\w+\.png)";
    const auto result = find_files(fs::current_path(), pattern);
    for (const auto& entry : result) {
        cout << entry.path().string() << endl;
    }
    return EXIT_SUCCESS;
}