#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Database { // Dependency 
    virtual int32_t get_population(const string& country) = 0;
};
class SingletonDatabase : Database {
    map<string, int32_t>    m_countries;
    SingletonDatabase() {
        ifstream ifs("countries.txt");
        string city, population;
        while (getline(ifs, city)) {
            getline(ifs, population);
            m_countries[city] = stoi(population);
        }
    }
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;
    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }
    int32_t get_population(const string& country) { return m_countries[country]; }
};
class DummyDatabase : public Database {
    map<string, int32_t>    m_countries;
public:
    DummyDatabase() : m_countries{ {"alpha", 1}, {"beta", 2}, {"gamma", 3} } {}
    int32_t get_population(const string& country) { return m_countries[country]; }
};
/* Testing class ------------------------------------------------------------ */
class ConfigurableRecordFinder {
    Database& m_db;  // Dependency Injection
public:
    ConfigurableRecordFinder(Database& db) : m_db{ db } {}
    int32_t total_population(const vector<string>& countries) {
        int32_t result = 0;
        for (auto& country : countries)
            result += m_db.get_population(country);
        return result;
    }
};
/* ------------------------------------------------------------------------- */
int main() {
    DummyDatabase db;
    ConfigurableRecordFinder rf(db);
    rf.total_population({ "Japan", "India", "America" });
    return EXIT_SUCCESS;
}
