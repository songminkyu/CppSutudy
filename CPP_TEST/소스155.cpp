
#include <iostream>
//Virtual Constructor 예제
//CRTP 패턴을 정적으로 이용할경우 참조 하라는거같은데....

struct animal {
    virtual ~animal() = default;
    virtual std::unique_ptr<animal> create() = 0;
    virtual std::unique_ptr<animal> clone() = 0;
};
struct dog : animal {
    std::unique_ptr<animal> create() { return std::make_unique<dog>(); }
    std::unique_ptr<animal> clone() { return std::make_unique<dog>(*this); }
};
struct cat : animal {
    std::unique_ptr<animal> create() { return std::make_unique<cat>(); }
    std::unique_ptr<animal> clone() { return std::make_unique<cat>(*this); }
};
void who_am_i(animal* who) {
    auto new_who = who->create();// `create` the object of same type i.e. pointed by who ?
    auto duplicate_who = who->clone(); // `copy` object of same type i.e. pointed by who ?    
    delete who; // you can delete object pointed by who
}

int main()
{
    cat *c = new cat();
    who_am_i(c);
}