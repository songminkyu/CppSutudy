#include <iostream>
#include <map>
#include <fstream>
#include <string>
using namespace std;


class SingletonDatabase {
    std::map<std::string, int32_t>  m_country;
    SingletonDatabase() {
        std::ifstream ifs("country.txt");
        std::string city, population;
        while (getline(ifs, city)) {
            getline(ifs, population);
            m_country[city] = stoi(population);
        }
    }
public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    SingletonDatabase& operator=(SingletonDatabase const&) = delete;
    static SingletonDatabase& get() {
        static SingletonDatabase db;
        return db;
    }
    int32_t get_population(const std::string& name) { return m_country[name]; }
};
int main() {

    /* country.txt
Japan
1000000
India
2000000
America
123500

파일에 내용이 없어서 에러 날수도있음 ㅋㅋㅋㅋ
*/

    SingletonDatabase::get().get_population("Japan");
    return EXIT_SUCCESS;
}
