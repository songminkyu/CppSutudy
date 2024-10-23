#include <string>
#include <iostream>
#include "Delegate.h"

int foo(const std::string& msg)
{
    std::cout << "\tfunction foo:" << msg << std::endl;

    return 100;
}

int bar(const std::string& msg)
{
    std::cout << "\tfunction bar:" << msg << std::endl;
    return 101;
}

class Foo
{
public:
    void member_function(const std::string& msg)
    {
        std::cout << "\tmember function of Foo class:" << msg << std::endl;
    }
};

class Bar
{
public:
    void member_function(const std::string& msg)
    {
        std::cout << "\tmember function of Bar class:" << msg << std::endl;

    }
};

int main()
{
    Foo fooObj;
    Bar barObj;

    Delegate<int, const std::string&> delegate;
    Delegate<void, const std::string&> vdelegate;
    // Delegate<> delegate; ���ø� ���ڰ� ���°��
    // Delegate delegate; C++17 ���ʹ� ���ڰ� ������ �ƿ� ���� ��

    //Return Ÿ��  
    delegate += foo;
    delegate += bar;
    auto lambda = [](const std::string& msg) {
        std::cout << "\tlambda:" << msg << std::endl;
        return 300;
    };
    delegate += lambda;
    for (auto itr = delegate.begin(); itr != delegate.end(); itr++)
    {
        std::cout << (*itr)("Hello World") << std::endl;
    }

    //void Ÿ��
    std::cout << "// add 'Foo::member_function' function" << std::endl;
    vdelegate += std::bind(&Foo::member_function, &fooObj, std::placeholders::_1);
    vdelegate("Hello World@@@@@@@@@");
    std::cout << std::endl;

    std::cout << "// add 'Bar::member_function' function" << std::endl;
    vdelegate += std::bind(&Bar::member_function, &barObj, std::placeholders::_1);
    vdelegate("Hello World");
    std::cout << std::endl;

    delegate -= foo;
    delegate -= bar;
    delegate -= lambda;
    vdelegate -= std::bind(&Foo::member_function, &fooObj, std::placeholders::_1);
    vdelegate -= std::bind(&Bar::member_function, &barObj, std::placeholders::_1);
}