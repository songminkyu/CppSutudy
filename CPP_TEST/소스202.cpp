#include <iostream>
#include <map>
#include <string>
#include <compare>

struct Person {
    int age;
    std::string name;
    friend auto operator<=>(Person const&, Person const&) = default;
};

struct Age { int value; };
struct Name { std::string value; };

struct Cmp {
    bool operator()(Person const& lhs, Person const& rhs) const { return (lhs <=> rhs) < 0; }
    bool operator()(Person const& lhs, Name const& name) const { std::cout << "#2-1\n"; return (lhs.name <=> name.value) < 0; }
    bool operator()(Name const& name, Person const& rhs) const { std::cout << "#2-2\n"; return (name.value <=> rhs.name) < 0; }
    bool operator()(Person const& lhs, Age const& age) const { std::cout << "#3-1\n"; return (lhs.age <=> age.value) < 0; }
    bool operator()(Age const& age, Person const& rhs) const { std::cout << "#3-2\n"; return (age.value <=> rhs.age) < 0; }

    using is_transparent = void;
};

int main() {
    std::map<Person, int, Cmp> datas{ {{10,"simmon10"},1}, { {20,"simmon20"}, 2} };
    auto iter1 = datas.find(Name{ "simmon10" });  std::cout << iter1->second << std::endl;
    auto iter2 = datas.find(Age{ 20 }); std::cout << iter2->second << std::endl;
}