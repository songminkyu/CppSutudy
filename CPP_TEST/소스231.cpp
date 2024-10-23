

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <type_traits>
#include <utility>
#include <string>



template <typename Key1, typename Key2, typename Value>
class doublekey_map
{
public:
    std::size_t size()
    {
        return map1.size();
    }

    void insert(Key1 _k1, Key2 _k2, Value* pV)
    {
        map1.insert(std::make_pair(_k1, pV));
        map2.insert(std::make_pair(_k2, pV));
    }

    typename std::map<Key1, Value*>::iterator find(const Key1& _key1)
    {
        return map1.find(_key1);
    }

    typename std::map<Key2, Value*>::iterator find(const Key2& _key2)
    {
        return map2.find(_key2);
    }

    Value& operator[](const Key1& _key1)
    {
        if (find(_key1) != end<Key1>())
            return *map1[_key1];
        else
            throw std::runtime_error("no such key!");
    }

    Value& operator[](const Key2& _key2)
    {
        if (find(_key2) != end<Key2>())
            return *map2[_key2];
        else
            throw std::runtime_error("no such key!");
    }

    template <typename Key>
    constexpr auto end()
    {
        static_assert(std::is_same_v<Key, Key1> || \
            std::is_same_v<Key, Key2>, \
            "Error! Bad template param for 'end()' method!");

        if constexpr (std::is_same_v<Key, Key1>)
            return map1.end();
        else if constexpr (std::is_same_v<Key, Key2>)
            return map2.end();
    }

    template <typename Key>
    constexpr auto begin()
    {
        static_assert(std::is_same_v<Key, Key1> || \
            std::is_same_v<Key, Key2>, \
            "Error! Bad template param for 'begin()' method!");

        if constexpr (std::is_same_v<Key, Key1>)
            return map1.begin();
        else if constexpr (std::is_same_v<Key, Key2>)
            return map2.begin();
    }

private:
    std::map<Key1, Value*> map1;
    std::map<Key2, Value*> map2;
};

namespace doublekey_map_tests
{
    //global data
    std::string s0 = "zero";
    std::string s1 = "one";
    std::string s2 = "two";

    bool testInsertRetrieveKey1andKey2()
    {
        doublekey_map<int, char, std::string> map;
        int k1 = 1;
        char k2 = '1';
        map.insert(k1, k2, &s1);

        //find by key1
        auto it1 = map.find(1);
        auto it2 = map.find('1');

        return (*it1->second == "one") && (*it2->second == "one");
    }

    bool testNoKey1()
    {
        doublekey_map<int, char, std::string> map;
        int k1 = 1;
        char k2 = '1';
        map.insert(k1, k2, &s1);

        auto it1 = map.find(2);
        auto endIt = map.end<int>();

        return (it1 == endIt);
    }

    bool testNoKey2()
    {
        doublekey_map<int, char, std::string> map;
        int k1 = 1;
        char k2 = '1';
        map.insert(k1, k2, &s1);

        auto it2 = map.find('2');
        auto endIt = map.end<char>();

        return (it2 == endIt);
    }

    bool testSize()
    {
        doublekey_map<int, char, std::string> map;

        map.insert(0, '0', &s0);
        map.insert(1, '1', &s1);
        map.insert(2, '2', &s2);

        return map.size() == 3;
    }

    template<typename First, typename Second>
    Second getSecond(const std::pair<First, Second*>& p)
    {
        return *p.second;
    }

    bool testStdAlgo()
    {
        doublekey_map<int, char, std::string> map;
        map.insert(0, '0', &s0);
        map.insert(1, '1', &s1);
        map.insert(2, '2', &s2);

        std::vector<std::string> sVect;
        std::transform(map.begin<int>(), map.end<int>(), std::back_inserter(sVect), getSecond<int, std::string >);

        return sVect[1] == s1;
    }


    bool testSquareBrackets()
    {
        doublekey_map<int, char, std::string> map;
        map.insert(1, '1', &s1);
        map.insert(2, '2', &s2);
        //get by key
        bool t1 = (map[1] == s1);
        bool t2 = (map['2'] == s2);
        //set by key
        map['1'] = s0;
        bool t3 = (map[1] == s0);
        //prevent with only one key
        bool t4 = false;
        try
        {
            map[3];
        }
        catch (std::runtime_error&)
        {
            t4 = true;
        }

        return t1 && t2 && t3 && t4;
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
        success &= launchTest("insert and retrieve keys", testInsertRetrieveKey1andKey2);
        success &= launchTest("no key1", testNoKey1);
        success &= launchTest("no key2", testNoKey2);
        success &= launchTest("size", testSize);
        success &= launchTest("Std algo compatibility", testStdAlgo);
        success &= launchTest("operator[] test", testSquareBrackets);
        if (success)
            std::cout << "All Double Key Map tests PASSED\n";
    }

} // doublekey_map_tests

int main()
{
    doublekey_map_tests::launchDoubleKeyMapTests();
}

