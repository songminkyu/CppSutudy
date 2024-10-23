#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <utility>

template <typename Key1, typename Key2, typename Value>
class doublekey_map
{
    std::map<Key1, size_t> keys1;
    std::map<Key2, size_t> keys2;
    std::vector<Value> values;
    // Your solution here!

public:
    void insert(std::tuple<Key1, Key2, Value> entry)
    {
        values.push_back(std::get<2>(entry));
        const auto index = values.size() - 1;
        keys1.insert({ std::get<0>(entry), index });
        keys2.insert({ std::get<1>(entry), index });
    }

    std::optional<Value>
        getValue(const Key1& key) const
    {
        if (const auto found = keys1.find(key); found != keys1.end())
        {
            return values[found->second];
        }
        else
        {
            return std::nullopt;
        }
    }

    std::optional<Value>
        getValue(const Key2& key) const
    {
        if (const auto found = keys2.find(key); found != keys2.end())
        {
            return values[found->second];
        }
        else
        {
            return std::nullopt;
        }
    }

    size_t size() const { return values.size(); }
};

namespace doublekey_map_tests
{

    // feel free to adapt those tests to your interface

    bool testInsertRetrieveKey1()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return map.getValue(2) && *map.getValue(2) == "two";
    }

    bool testInsertRetrieveKey2()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return map.getValue('2') && *map.getValue('2') == "two";
    }

    bool testNoKey1()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return !map.getValue(3);
    }

    bool testNoKey2()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(std::make_tuple(2, '2', "two"));

        return !map.getValue('3');
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