#include <optional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <tuple>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/global_fun.hpp>
using namespace boost::multi_index;

template <typename Key1, typename Key2, typename Value>
class doublekey_map
{
private:
    using Item = std::tuple<Key1, Key2, Value>;

    static const Key1& get_key1(const Item& item) { return std::get<0>(item); }
    static const Key2& get_key2(const Item& item) { return std::get<1>(item); }

    using item_set = boost::multi_index_container<
        Item,
        indexed_by<
        ordered_unique<global_fun<const Item&, const Key1&, &doublekey_map::get_key1>>,
        ordered_unique<global_fun<const Item&, const Key2&, &doublekey_map::get_key2>>
        >>;
    item_set items;

public:
    void insert(std::tuple<Key1, Key2, Value> entry)
    {
        items.template get<0>().insert(std::move(entry));
    }

    std::optional<Value> getValue(const Key1& key) const
    {
        auto& index = items.template get<0>();
        auto item = index.find(key);
        if (item != index.end())
            return std::get<2>(*item);
        else
            return std::nullopt;
    }

    std::optional<Value> getValue(const Key2& key) const
    {
        auto& index = items.template get<1>();
        auto item = index.find(key);
        if (item != index.end())
            return std::get<2>(*item);
        else
            return std::nullopt;
    }

    size_t size() const
    {
        return items.size();
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
        doublekey_map<int, std::string, std::string> map;

        map.insert(std::make_tuple(2, "2", "two"));
        std::cout << map.getValue("2").value() << std::endl;
        return map.getValue("2") && *map.getValue("2") == "two";
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

