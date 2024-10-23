#include<iostream>
using namespace std;

class CParent
{
public:
    CParent& operator = (const CParent& obj)
    {
        cout << "CParent::operator=" << endl;
        return *this;
    }

    virtual void pasongsong()
    {

    }
};

class CTestA : CParent
{
public:
    CTestA& operator = (const CTestA& obj) 
    {
        cout << "CTestA::operator" << endl;
        return *this;
    }
    void pasongsong() override
    {
        std::cout << "CTestA asdasdasd" << std::endl;
    }
};

class CTestB : public CParent
{
public:

};

int main()
{
   /* CTestA a1;    
    CTestA a2;
    a2 = a1;

    CTestB b1;
    CTestB b2;
    b2 = b1;*/

    int x = 6;    
    int* xx = &x;
        
    std::cout << ++x << std::endl;
    std::cout << --(*xx) << std::endl;
    std::cout << ++(*xx) << std::endl;

}