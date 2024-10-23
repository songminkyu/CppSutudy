#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

template <typename Key1, typename Key2, typename Value>
class doublekey_map
    : public std::map<std::pair<Key1, Key2>, Value>
{
    using base = std::map<std::pair<Key1, Key2>, Value>;
public:
    void insert(std::tuple<Key1, Key2, Value> entry)
    {
        auto key = std::make_pair(std::get<0>(entry), std::get<1>(entry));
        base::insert(std::make_pair(key, std::get<2>(entry)));
        map1.insert(std::make_pair(std::get<0>(entry), key));
        map2.insert(std::make_pair(std::get<1>(entry), key));
    }
    void clear() { base::clear(); map1.clear(); map2.clear(); } //TODO: apply the same for erase()

    typename base::const_iterator find(const Key1& key1) const
    {
        auto it = map1.find(key1);
        if (it == map1.end()) return base::cend();
        return base::find(it->second);
    }
    typename base::const_iterator find(const Key2& key2) const
    {
        auto it = map2.find(key2);
        if (it == map2.end()) return base::cend();
        return base::find(it->second);
    }
private:
    std::map<Key1, std::pair<Key1, Key2>> map1;
    std::map<Key2, std::pair<Key1, Key2>> map2;

};

namespace doublekey_map_tests
{

    // feel free to adapt those tests to your interface

    bool testInsertRetrieveKey1()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return map.find(2) != map.end() && map.find(2)->second == "two";
    }

    bool testInsertRetrieveKey2()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return map.find('2') != map.end() && map.find(2)->second == "two";
    }

    bool testNoKey1()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return map.find(3) == map.end();
    }

    bool testNoKey2()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return map.find('3') == map.end();
    }

    bool testSize()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(0, '0', "zero"));
        map.insert(std::make_tuple(1, '1', "one"));
        map.insert(std::make_tuple(2, '2', "two"));

        return map.size() == 3;
    }

    template <typename TestFunction>
    bool launchTest(std::string const& testName, TestFunction testFunction)
    {
        const bool success = testFunction();
        if (!success)
            std::cout << "Test - " << testName << ": FAILED\n";
        return success;
    }

    void launchDoubleKeyMapTests()
    {
        bool success = true;
        success &= launchTest("insert and retrieve key1", testInsertRetrieveKey1);
        success &= launchTest("insert and retrieve key2", testInsertRetrieveKey2);
        success &= launchTest("no key1", testNoKey1);
        success &= launchTest("no key2", testNoKey2);
        success &= launchTest("size", testSize);
        if (success)
            std::cout << "All Double Key Map tests PASSED\n";
    }

} // doublekey_map_tests

int main()
{
    doublekey_map_tests::launchDoubleKeyMapTests();
}
