#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <utility>

template <typename Key1, typename Key2, typename Value>
class doublekey_map
{
private:
    using entry_t = std::tuple<Key1, Key2, Value>;
    using value_ptr_t = typename std::add_pointer<Value>::type;

    std::map<Key1, Value> m1;
    std::map<Key2, value_ptr_t> m2;

public:
    void insert(const entry_t& entry)
    {
        auto key1{ std::get<0>(entry) };
        auto key2{ std::get<1>(entry) };

        m1.insert(std::make_pair(key1, std::get<2>(entry)));

        auto entered_itr = m1.find(key1);
        value_ptr_t val_ptr = &(entered_itr->second);

        m2.insert(std::make_pair(key2, val_ptr));
    }

    std::optional<Value> getValue(const Key1& key) const
    {
        auto ret = m1.find(key);
        if (ret == end(m1))
        {
            return std::nullopt;
        }
        return ret->second;
    }

    std::optional<Value> getValue(const Key2& key) const
    {
        auto ret = m2.find(key);
        if (ret == end(m2))
        {
            return std::nullopt;
        }
        return *(ret->second);
    }

    size_t size() const
    {
        return m1.size();
    }
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

} // namespace doublekey_map_tests

int main()
{
    doublekey_map_tests::launchDoubleKeyMapTests();
}