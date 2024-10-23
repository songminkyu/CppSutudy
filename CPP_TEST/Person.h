#pragma once
#include <iostream>
using namespace std;
class PersonBuilder;
class Person
{
    std::string m_name, m_street_address, m_post_code, m_city;  // Personal Detail
    std::string m_company_name, m_position, m_annual_income;    // Employment Detail
    Person(std::string name) : m_name(name) {}
public:
    friend class PersonBuilder;
    friend ostream& operator<<(ostream& os, const Person& obj);
    static PersonBuilder create(std::string name);
};