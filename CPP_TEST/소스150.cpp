#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

enum class Importance { PRIMARY, SECONDARY, TERTIARY };
template <typename T, typename Key = std::string>
struct Multiton {
    static shared_ptr<T> get(const Key& key) {
        if (const auto it = m_instances.find(key); it != m_instances.end()) { // C++17
            return it->second;
        }
        return m_instances[key] = make_shared<T>();
    }
private:
    static map<Key, shared_ptr<T>>  m_instances;
};
template <typename T, typename Key>
map<Key, shared_ptr<T>>     Multiton<T, Key>::m_instances; // Just initialization of static data member
struct Printer {
    Printer() { cout << "Total instances so far = " << ++InstCnt << endl; }
private:
    static int InstCnt;
};
int Printer::InstCnt = 0;
int main() {
    using mt = Multiton<Printer, Importance>;
    auto main = mt::get(Importance::PRIMARY);
    auto aux = mt::get(Importance::SECONDARY);
    auto aux2 = mt::get(Importance::SECONDARY); // Will not create additional instances
    return EXIT_SUCCESS;
}