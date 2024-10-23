#include <iostream>
using namespace std;

//http://www.vishalchovatiya.com/facade-design-pattern-in-modern-cpp/

struct Alarm {
    void alarm_on() { cout << "Alarm is on and house is secured" << endl; }
    void alarm_off() { cout << "Alarm is off and you can go into the house" << endl; }
};
struct Ac {
    void ac_on() { cout << "Ac is on" << endl; }
    void ac_off() { cout << "AC is off" << endl; }
};
struct Tv {
    void tv_on() { cout << "Tv is on" << endl; }
    void tv_off() { cout << "TV is off" << endl; }
};
struct HouseFacade {
    void go_to_work() {
        m_ac.ac_off();
        m_tv.tv_off();
        m_alarm.alarm_on();
    }
    void come_home() {
        m_alarm.alarm_off();
        m_ac.ac_on();
        m_tv.tv_on();
    }
private:
    Alarm   m_alarm;
    Ac      m_ac;
    Tv      m_tv;
};
int main() {
    HouseFacade hf;
    //Rather than calling 100 different on and off functions thanks to facade I only have 2 functions...
    hf.go_to_work();
    hf.come_home();
    return EXIT_SUCCESS;
}