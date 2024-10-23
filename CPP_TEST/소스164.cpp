#include <boost/bimap.hpp>
#include <iostream>
#include <string>
using namespace std;

struct User {
    User(string f, string l) : m_first_name{ add(f) }, m_last_name{ add(l) } { }
    string get_first_name() { return names.left.find(m_first_name)->second; }
    string get_last_name() { return names.left.find(m_last_name)->second; }
    friend ostream& operator<<(ostream& os, User& obj) {
        return os <<
            obj.get_first_name() << "(id=" << obj.m_first_name << "), " <<
            obj.get_last_name() << "(id=" << obj.m_last_name << ")";
    }
protected:
    using key = uint32_t;
    static boost::bimap<key, string>        names;
    static key                              seed;
    static key add(string s) {
        auto it = names.right.find(s);
        if (it == names.right.end()) {
            names.insert({ ++seed, s });
            return seed;
        }
        return it->second;
    }
    key     m_first_name, m_last_name;
};
User::key                           User::seed = 0;
boost::bimap<User::key, string>     User::names{};
int main() {
    User john_doe{ "John","Doe" };
    User jane_doe{ "Jane","Doe" };
    cout << "John Details: " << john_doe << endl;
    cout << "Jane Details: " << jane_doe << endl;
    return EXIT_SUCCESS;
}