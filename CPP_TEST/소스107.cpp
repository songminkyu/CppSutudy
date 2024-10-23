
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <random>
#include <numeric>
#include <functional>
#include <meta\meta.hpp>
#include <chrono>
#include <type_traits>
template <typename ForwardIterator, typename OutputIterator, typename Equal, typename Merge>
void merge_adjacent(ForwardIterator first, ForwardIterator last, OutputIterator out, Equal equal, Merge merge)
{
    auto beginUnique = first;
    while (beginUnique != last)
    {
        // output all unique elements; stop when finding indentical adjacent ones
        auto endUnique = std::adjacent_find(beginUnique, last, equal);
        out = std::copy(beginUnique, endUnique, out);

        // identify the range of identical adjacent elements
        auto beginIdentical = endUnique;
        auto endIdentical = std::find_if_not(beginIdentical, last, [beginIdentical, equal](auto const& element) {return equal(element, *beginIdentical); });

        // aggregate identical flows into one
        if (beginIdentical != endIdentical)
        {
            if (std::distance(beginIdentical, endIdentical) == 1)
            {
                *out = *beginIdentical;
            }
            else
            {
                *out = std::accumulate(std::next(beginIdentical), endIdentical, *beginIdentical, merge);
            }
            ++out;
        }
        beginUnique = endIdentical;
    }
}

template <typename ForwardIterator, typename OutputIterator>
OutputIterator mergeAdjacent(ForwardIterator first, ForwardIterator last, OutputIterator results)
{
    ForwardIterator beginUnique = first;
    while (beginUnique != last)
    {
        // output all unique elements; stop when finding indentical adjacent ones
        ForwardIterator endUnique = std::adjacent_find(beginUnique, last);
        results = std::copy(beginUnique, endUnique, results);

        // identify the range of identical adjacent elements
        ForwardIterator beginIdentical = endUnique;
        ForwardIterator endIdentical = std::find_if(beginIdentical, last, [beginIdentical](const auto& element) {return element != *beginIdentical; });

        // aggregate identical flows into one
        if (beginIdentical != endIdentical)
        {
            *results = std::accumulate(beginIdentical, endIdentical, typename ForwardIterator::value_type());
            ++results;
        }
        beginUnique = endIdentical;
    }
    return results;
}

template <typename ForwardIterator, typename OutputIterator, typename Equal, typename Merge>
void merge_adjacent_jb(ForwardIterator first, ForwardIterator last, OutputIterator out, Equal equal, Merge merge)
{
    for (auto beginUnique = first, endIdentical = first; beginUnique != last; beginUnique = endIdentical) {
        // output all unique elements; stop when finding identical adjacent ones
        const auto beginIdentical = std::adjacent_find(beginUnique, last, equal);

        out = std::copy(beginUnique, beginIdentical, out);

        // identify the range of identical adjacent elements
        endIdentical = std::find_if_not(beginIdentical, last, [beginIdentical, equal](auto const& element) {return equal(element, *beginIdentical); });

        // aggregate identical flows into one
        if (beginIdentical != endIdentical)
            *out++ = (std::distance(beginIdentical, endIdentical) == 1) ? *beginIdentical : std::accumulate(std::next(beginIdentical), endIdentical, *beginIdentical, merge);
    }
}

/////////// SALE CLASS /////////////////////////////////
template<class Key, class Value>
class UnroMap
{
public:
    UnroMap(Key _key, Value _value) : _Key(_key), _Value(_value) {}
    Key getKey() const { return _Key; }
    Value getValue() const { return _Value; }

private:
    Key _Key;
    Value _Value;
};


template<class Key, class Value>
bool operator==(UnroMap<Key, Value> const& sale1, UnroMap<Key, Value> const& sale2)
{
    return sale1.getKey() == sale2.getKey() && sale1.getValue() == sale2.getValue();
}

bool sameDate(UnroMap<int, int> const& sale1, UnroMap<int, int> const& sale2)
{
    return sale1.getKey() == sale2.getKey();
}
UnroMap<int, int> mergeSales(UnroMap<int, int> const& sale1, UnroMap<int, int> const& sale2)
{
    if (sale1.getKey() != sale2.getKey()) throw "Error: cannot add sales with different dates";

    return UnroMap(sale1.getKey(), sale1.getValue() + sale2.getValue());
}

bool sameStringDate(UnroMap<int, std::string> const& sale1, UnroMap<int, std::string> const& sale2)
{
    return sale1.getKey() == sale2.getKey();
}
UnroMap<int, std::string> mergeStringSales(UnroMap<int, std::string> const& sale1, UnroMap<int, std::string> const& sale2)
{
    if (sale1.getKey() != sale2.getKey()) throw "Error: cannot add sales with different dates";

    return UnroMap(sale1.getKey(), sale1.getValue() + sale2.getValue());
}

bool sameStrStrDate(UnroMap<std::string, std::string> const& sale1, UnroMap<std::string, std::string> const& sale2)
{
    return sale1.getKey() == sale2.getKey();
}
UnroMap<std::string, std::string> mergesStrStrSales(UnroMap<std::string, std::string> const& sale1, UnroMap<std::string, std::string> const& sale2)
{
    if (sale1.getKey() != sale2.getKey()) throw "Error: cannot add sales with different dates";

    return UnroMap(sale1.getKey(), sale1.getValue() + sale2.getValue());
}


////////////////////////////////////////////////////////


/////////// TEST CODE: MAKE IT PASS! ///////////////////
template<class Key, class Value>
std::vector<UnroMap<Key, Value>> aggregateDailySales(std::vector<UnroMap<Key, Value>> const& sales)
{
    std::vector<UnroMap<Key, Value>> dailySales;

    if constexpr ((std::is_same<Key, int>::value == true) && (std::is_same<Value, int>::value == true)) {
        merge_adjacent_jb(begin(sales), end(sales), std::back_inserter(dailySales), sameDate, mergeSales);
    }
    else if constexpr ((std::is_same<Key, int>::value == true) && (std::is_same<Value, std::string>::value == true)) {
        merge_adjacent_jb(begin(sales), end(sales), std::back_inserter(dailySales), sameStringDate, mergeStringSales);
    }
    else if constexpr ((std::is_same<Key, std::string>::value == true) && (std::is_same<Value, std::string>::value == true)) {
        merge_adjacent_jb(begin(sales), end(sales), std::back_inserter(dailySales), sameStrStrDate, mergesStrStrSales);
    }
    return dailySales;
}

bool test1()
{
    auto sales = std::vector<UnroMap<int, int>>{ {1, 12}, {1, 5}, {1, 6}, {3, 7}, {5, 1}, {5, 1}, {5, 3} };
    auto expected = std::vector<UnroMap<int, int>>{ {1, 23}, {3, 7}, {5, 5} };
    return aggregateDailySales(sales) == expected;
}

bool test2()
{
    auto sales = std::vector<UnroMap<int, int>>{ {1, 12}, {1, 5}, {1, 6}, {5, 1}, {5, 1}, {5, 3} };
    auto expected = std::vector<UnroMap<int, int>>{ {1, 23}, {5, 5} };
    return aggregateDailySales(sales) == expected;
}

bool test3()
{
    auto sales = std::vector<UnroMap<int, int>>{ {1, 12}, {3, 5}, {3, 6}, {3, 7} };
    auto expected = std::vector<UnroMap<int, int>>{ {1, 12}, {3, 18} };
    return aggregateDailySales(sales) == expected;
}

bool test4()
{
    auto sales = std::vector<UnroMap<int, int>>{ {3, 5}, {3, 6}, {3, 7}, {4, 13} };
    auto expected = std::vector<UnroMap<int, int>>{ {3, 18}, {4, 13} };
    return aggregateDailySales(sales) == expected;
}

bool test5()
{
    auto sales = std::vector<UnroMap<int, int>>{ {3, 5}, {3, 6}, {3, 7} };
    auto expected = std::vector<UnroMap<int, int>>{ {3, 18} };
    return aggregateDailySales(sales) == expected;
}

bool test6()
{
    auto sales = std::vector<UnroMap<int, int>>{ {3, 5} };
    auto expected = std::vector<UnroMap<int, int>>{ {3, 5} };
    return aggregateDailySales(sales) == expected;
}

bool test7()
{
    auto sales = std::vector<UnroMap<int, int>>{};
    auto expected = std::vector<UnroMap<int, int>>{};
    return aggregateDailySales(sales) == expected;
}

bool test8()
{
    auto sales = std::vector<UnroMap<int, std::string>>{ {1,"song"},{1,"min"},{1,"kyu"} };
    auto expected = std::vector<UnroMap<int, std::string>>{ {1,"songminkyu"} };
    return aggregateDailySales(sales) == expected;
}

bool test9()
{
    auto sales = std::vector<UnroMap<std::string, std::string>>{ {"AA","song"},{"AA","min"},{"AA","kyu"} };
    auto expected = std::vector<UnroMap<std::string, std::string>>{ {"AA","songminkyu"} };
    return aggregateDailySales(sales) == expected;
}



int main()
{
    auto start = std::chrono::system_clock::now();

    std::cout << "TEST 1: " << (test1() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 2: " << (test2() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 3: " << (test3() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 4: " << (test4() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 5: " << (test5() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 6: " << (test6() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 7: " << (test7() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 8: " << (test8() ? "PASSED" : "FAILED") << '\n';
    std::cout << "TEST 9: " << (test9() ? "PASSED" : "FAILED") << '\n';
    auto end = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
   
    std::cout << time.count() << std::endl;
  
}

////////////////////////////////////////////////////////
