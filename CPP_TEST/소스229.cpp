#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

namespace detail {
    template <typename K1, typename K2>
    struct keycomp {
        using key_pair = std::pair<K1, K2>;

        using is_transparent = void;

        bool operator()(key_pair const& kp, K1 const& k) const {
            return kp.first < k;
        }
        bool operator()(key_pair const& kp, K2 const& k) const {
            return kp.second < k;
        }
        bool operator()(K1 const& k, key_pair const& kp) const {
            return k < kp.first;
        }
        bool operator()(K2 const& k, key_pair const& kp) const {
            return k < kp.second;
        }
        bool operator()(key_pair const& lho, key_pair const& rho) {
            return lho < rho;
        }
    };
}  // namespace detail

template <typename Key1, typename Key2, typename Value>
class doublekey_map {
    using key_pair = std::pair<Key1, Key2>;
    using repr_type = std::map<key_pair, Value, detail::keycomp<Key1, Key2>>;

public:
    using value_type = typename repr_type::value_type;
    using iterator = typename repr_type::iterator;

    void insert(value_type const& value) { m_rep.insert(value); }

    auto begin() { return m_rep.begin(); }
    auto end() { return m_rep.end(); }

    template <typename Key>
    auto find(Key const& k)
        -> std::enable_if_t<std::is_convertible<Key, Key1>::value or
        std::is_convertible<Key, Key2>::value,
        iterator> {
        return m_rep.find(k);
    }

    size_t size() const { return m_rep.size(); }

private:
    repr_type m_rep{};
};

namespace doublekey_map_tests {

    // feel free to adapt those tests to your interface

    bool testInsertRetrieveKey1() {
        doublekey_map<int, char, std::string> map;

        map.insert({ {2, '2'}, "two" });

        auto it = map.find(2);
        return it != map.end() && it->second == "two";
    }

    bool testInsertRetrieveKey2() {
        doublekey_map<int, char, std::string> map;

        map.insert({ {2, '2'}, "two" });

        auto it = map.find('2');
        return it != map.end() && it->second == "two";
        ;
    }

    bool testNoKey1() {
        doublekey_map<int, char, std::string> map;

        map.insert({ {2, '2'}, "two" });
        return map.find(3) == map.end();
    }

    bool testNoKey2() {
        doublekey_map<int, char, std::string> map;

        map.insert({ {2, '2'}, "two" });

        return map.find('3') == map.end();
    }

    bool testSize() {
        doublekey_map<int, char, std::string> map;

        map.insert({ {0, '0'}, "zero" });
        map.insert({ {1, '1'}, "one" });
        map.insert({ {2, '2'}, "two" });

        return map.size() == 3;
    }
    bool testKeyComparationFunctor() {
        auto kc = detail::keycomp<int, char>{};
        auto result = !kc({ 1, '1' }, 1);
        result &= !kc(1, { 1, '1' });
        result &= !kc({ 1, '1' }, '1');
        result &= !kc('1', { 1, '1' });
        result &= !kc({ 2, '2' }, 1);
        result &= kc(1, { 2, '2' });
        result &= !kc({ 2, '2' }, '1');
        result &= kc('1', { 2, '2' });
        result &= !kc({ 2, '2' }, { '1' });
        result &= kc('1', { 2, '2' });
        return result;
    }

    template <typename TestFunction>
    bool launchTest(std::string const& testName, TestFunction testFunction) {
        const bool success = testFunction();
        if (!success) std::cout << "Test - " << testName << ": FAILED\n";
        return success;
    }

    void launchDoubleKeyMapTests() {
        bool success = true;
        success &= launchTest("key comparation functor", testKeyComparationFunctor);
        success &= launchTest("insert and retrieve key1", testInsertRetrieveKey1);
        success &= launchTest("insert and retrieve key2", testInsertRetrieveKey2);
        success &= launchTest("no key1", testNoKey1);
        success &= launchTest("no key2", testNoKey2);
        success &= launchTest("size", testSize);
        if (success) std::cout << "All Double Key Map tests PASSED\n";
    }

}  // namespace doublekey_map_tests

int main() { doublekey_map_tests::launchDoubleKeyMapTests(); }